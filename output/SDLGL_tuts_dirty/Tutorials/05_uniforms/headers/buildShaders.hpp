

GLuint buildShaders(int shader_program_handle, const char *vertexShaderSourceParam, const char *fragmentShaderSourceParam){
    printf("building shaders...\n");
    shader_program_handle = glCreateProgram();
        // build and compile our shader program
    // ------------------------------------

    // open file and convert it to string for vs:
    char * vbuffer = 0;
    long vlength;
    FILE * vertex_file = fopen (vertexShaderSourceParam, "rb");

    if (vertex_file)
    {
      fseek (vertex_file, 0, SEEK_END);
      vlength = ftell (vertex_file);
      fseek (vertex_file, 0, SEEK_SET);
      vbuffer = (char *) malloc (vlength + 1);
      if (vbuffer)
      {
        fread (vbuffer, 1, vlength, vertex_file);
      }
      fclose (vertex_file);
      vbuffer[vlength] = '\0';
    }

    char * fbuffer = 0;
    long flength;
    FILE * fragment_file = fopen (fragmentShaderSourceParam, "rb");

    if (fragment_file)
    {
      fseek (fragment_file, 0, SEEK_END);
      flength = ftell (fragment_file);
      fseek (fragment_file, 0, SEEK_SET);
      fbuffer = (char *) malloc (flength + 1);
      if (fbuffer)
      {
        fread (fbuffer, 1, flength, fragment_file);
      }
      fclose (fragment_file);
      fbuffer[flength] = '\0';
    }

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vbuffer, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fbuffer, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
    }
    // link shaders
    // int shaderProgram = glCreateProgram();
    glAttachShader(shader_program_handle, vertexShader);
    glAttachShader(shader_program_handle, fragmentShader);
    glLinkProgram(shader_program_handle);
    // check for linking errors
    glGetProgramiv(shader_program_handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_handle, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shader_program_handle;
}
