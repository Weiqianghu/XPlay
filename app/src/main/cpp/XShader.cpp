//
// Created by weiqianghu on 2019/6/11.
//

#include <GLES2/gl2.h>
#include "XLog.h"
#include "XShader.h"

#define GET_STR(x) #x
static const char *vertexShader = GET_STR(
        attribute
        vec4 aPosition;
        attribute
        vec2 aTexCoord;
        varying
        vec2 vTexCoord;
        void main() {
            vTexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
            gl_Position = aPosition;
        }
);

static const char *fragYUV420p = GET_STR(
        precision
        mediump float;
        varying
        vec2 vTexCoord;
        uniform
        sampler2D yTexture;
        uniform
        sampler2D uTexture;
        uniform
        sampler2D vTexture;

        void main() {
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture, vTexCoord).r;
            yuv.g = texture2D(uTexture, vTexCoord).r - 0.5;
            yuv.b = texture2D(vTexture, vTexCoord).r - 0.5;
            rgb = mat3(1.0, 1.0, 1.0,
                       0.0, -0.39465, 2.03211,
                       1.13983, -0.58060, 0.0
            ) * yuv;

            gl_FragColor = vec4(rgb, 1.0);
        }
);

static GLuint InitShader(const char *code, GLint type) {
    GLuint sh = glCreateShader(type);
    if (sh == 0) {
        XLOGE("glCreateShader failed %d", type);
        return 0;
    }

    glShaderSource(sh, 1, &code, 0);
    glCompileShader(sh);

    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        XLOGE("glCompileShader failed");
        return 0;
    }

    return sh;
}

bool XShader::Init() {
    vsh = InitShader(vertexShader, GL_VERTEX_SHADER);
    if (vsh == 0) {
        XLOGE("InitShader vertex shader fail");
        return false;
    }
    XLOGD("InitShader vertex shader success");
    fsh = InitShader(fragYUV420p, GL_FRAGMENT_SHADER);
    if (fsh == 0) {
        XLOGE("InitShader frag shader fail");
        return false;
    }
    XLOGD("InitShader frag shader success");

    program = glCreateProgram();
    if (program == 0) {
        XLOGE("glCreateProgram failed!");
        return false;
    }

    glAttachShader(program, vsh);
    glAttachShader(program, fsh);

    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        XLOGE("gl link failed!");
        return false;
    }
    XLOGD("gl link success!");

    glUseProgram(program);

    static float vers[] = {
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f
    };
    GLuint apos = (GLuint) glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(apos);
    glVertexAttribPointer(apos, 3, GL_FLOAT, GL_FALSE, 12, vers);

    int width = 424, height = 240;
    static float txts[] = {
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };
    GLuint atext = (GLuint) glGetAttribLocation(program, "aTexCoord");
    glEnableVertexAttribArray(atext);
    glVertexAttribPointer(atext, 2, GL_FLOAT, GL_FALSE, 8, txts);

    glUniform1i(glGetUniformLocation(program, "yTexture"), 0);
    glUniform1i(glGetUniformLocation(program, "uTexture"), 1);
    glUniform1i(glGetUniformLocation(program, "vTexture"), 2);

    XLOGD("shader init success");

    return true;
}
