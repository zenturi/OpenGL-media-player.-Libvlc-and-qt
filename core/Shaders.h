const char * FProgram = "\
           varying vec4 pos;\
           varying vec2 vTexCoord;\
           varying float tex;\
           varying float pos_m;\
           uniform float is_anaglyph;\
           uniform sampler2D y_tex;\
           void main( void )\
           {    \
               \
               vec4 Y;\
               \
               if(is_anaglyph == 1.0){\
                   if(tex==1.0){\
                       Y = texture2D(y_tex, vTexCoord).rgba;\
                   } else {\
                       Y = texture2D(y_tex, vTexCoord * vec2(1.0, 1.0)).rgba;\
                   }\
               } else {\
                   Y = texture2D(y_tex, vTexCoord + vec2(0.0, 0.0)).rgba;\
               }\
                \
               vec4 color_r, v_color;\
               \
               float y=1.1643*(Y.r-0.0625);\
               float u=Y.g-0.5;\
               float v=Y.a-0.5;\
               float r=y+1.5958*v;\
               float g=y-0.39173*u-0.81290*v;\
               float b=y+2.017*u;\
               \
               if(is_anaglyph == 0.0){\
                v_color = vec4(r, g, b, 1.0);\
               } else {\
                color_r = texture2D(y_tex, vTexCoord + vec2(0.16, 0.0)).rgba;\
                v_color = vec4(1.0, g, b, 1.0) * vec4(color_r.r, 1.0, 1.0, 1.0);\
               }\
               gl_FragColor = v_color;\
           }";


 const char* YUV420P_VS ="\
            varying vec4 pos;\
            varying vec4 color;\
            uniform float scale;\
            attribute vec2 position;\
            uniform vec2 size_frame;\
            varying float tex;\
            varying float pos_m;\
            varying vec2 vTexCoord;\
            void main(){\
                 tex = scale;\
                 vTexCoord = position.xy * vec2(1.0, 1.0) + vec2(0.0, 0.0);\
                 float angle = 3.14/180.0 * 180.0;\
                 \
                 \
                 mat4 translate = mat4(\
                             vec4( 1.0,  0.0,  0.0, -0.5),\
                             vec4(0.0,  1.0,  0.0, -0.5),\
                             vec4(0.0,  0.0,  1.0, 0.0),\
                             vec4(0.0,  0.0,  0.0, 1.0)\
                           );\
                 \
                 \
                 \
                 vec4 vec_rotate = vec4(position.xy, 0.0, 1.0);\
                 vec_rotate = vec_rotate * translate;\
                 vec3 rot = vec_rotate.xyz;\
                 gl_Position = vec4(rot.x * size_frame.x, -rot.y * size_frame.y, 0.0, 1.0);\
               }";
