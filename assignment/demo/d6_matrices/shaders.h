/* Generated by bin2c, do not edit manually */

/* Contents of file d6_matrices/SimpleTransform.glsl */
const long int vertexshader_size = 359;
const unsigned char vertexshader[359] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x33, 0x33, 0x30, 0x20, 0x63, 0x6F, 0x72,
    0x65, 0x0A, 0x0A, 0x2F, 0x2F, 0x20, 0x49, 0x6E, 0x70, 0x75, 0x74, 0x20, 0x76, 0x65, 0x72, 0x74,
    0x65, 0x78, 0x20, 0x64, 0x61, 0x74, 0x61, 0x2C, 0x20, 0x64, 0x69, 0x66, 0x66, 0x65, 0x72, 0x65,
    0x6E, 0x74, 0x20, 0x66, 0x6F, 0x72, 0x20, 0x61, 0x6C, 0x6C, 0x20, 0x65, 0x78, 0x65, 0x63, 0x75,
    0x74, 0x69, 0x6F, 0x6E, 0x73, 0x20, 0x6F, 0x66, 0x20, 0x74, 0x68, 0x69, 0x73, 0x20, 0x73, 0x68,
    0x61, 0x64, 0x65, 0x72, 0x2E, 0x0A, 0x6C, 0x61, 0x79, 0x6F, 0x75, 0x74, 0x28, 0x6C, 0x6F, 0x63,
    0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x3D, 0x20, 0x30, 0x29, 0x20, 0x69, 0x6E, 0x20, 0x76, 0x65,
    0x63, 0x33, 0x20, 0x76, 0x65, 0x72, 0x74, 0x65, 0x78, 0x50, 0x6F, 0x73, 0x69, 0x74, 0x69, 0x6F,
    0x6E, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x73, 0x70, 0x61, 0x63, 0x65, 0x3B, 0x0A, 0x0A, 0x2F,
    0x2F, 0x20, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x73, 0x20, 0x74, 0x68, 0x61, 0x74, 0x20, 0x73, 0x74,
    0x61, 0x79, 0x20, 0x63, 0x6F, 0x6E, 0x73, 0x74, 0x61, 0x6E, 0x74, 0x20, 0x66, 0x6F, 0x72, 0x20,
    0x74, 0x68, 0x65, 0x20, 0x77, 0x68, 0x6F, 0x6C, 0x65, 0x20, 0x6D, 0x65, 0x73, 0x68, 0x2E, 0x0A,
    0x75, 0x6E, 0x69, 0x66, 0x6F, 0x72, 0x6D, 0x20, 0x6D, 0x61, 0x74, 0x34, 0x20, 0x4D, 0x61, 0x74,
    0x72, 0x69, 0x78, 0x3B, 0x0A, 0x0A, 0x76, 0x6F, 0x69, 0x64, 0x20, 0x6D, 0x61, 0x69, 0x6E, 0x28,
    0x29, 0x7B, 0x0A, 0x0A, 0x09, 0x2F, 0x2F, 0x20, 0x4F, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x70,
    0x6F, 0x73, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x6F, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x76,
    0x65, 0x72, 0x74, 0x65, 0x78, 0x2C, 0x20, 0x69, 0x6E, 0x20, 0x63, 0x6C, 0x69, 0x70, 0x20, 0x73,
    0x70, 0x61, 0x63, 0x65, 0x20, 0x3A, 0x20, 0x4D, 0x61, 0x74, 0x72, 0x69, 0x78, 0x20, 0x2A, 0x20,
    0x70, 0x6F, 0x73, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x0A, 0x09, 0x67, 0x6C, 0x5F, 0x50, 0x6F, 0x73,
    0x69, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x3D, 0x20, 0x20, 0x4D, 0x61, 0x74, 0x72, 0x69, 0x78, 0x20,
    0x2A, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x76, 0x65, 0x72, 0x74, 0x65, 0x78, 0x50, 0x6F, 0x73,
    0x69, 0x74, 0x69, 0x6F, 0x6E, 0x5F, 0x6D, 0x6F, 0x64, 0x65, 0x6C, 0x73, 0x70, 0x61, 0x63, 0x65,
    0x2C, 0x31, 0x29, 0x3B, 0x0A, 0x0A, 0x7D
};

/* Contents of file d6_matrices/SingleColor.glsl */
const long int fragmentshader_size = 115;
const unsigned char fragmentshader[115] = {
    0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x33, 0x33, 0x30, 0x20, 0x63, 0x6F, 0x72,
    0x65, 0x0A, 0x0A, 0x2F, 0x2F, 0x20, 0x4F, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x64, 0x61, 0x74,
    0x61, 0x0A, 0x6F, 0x75, 0x74, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x63, 0x6F, 0x6C, 0x6F, 0x72,
    0x3B, 0x0A, 0x0A, 0x76, 0x6F, 0x69, 0x64, 0x20, 0x6D, 0x61, 0x69, 0x6E, 0x28, 0x29, 0x0A, 0x7B,
    0x0A, 0x0A, 0x09, 0x2F, 0x2F, 0x20, 0x4F, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x63, 0x6F, 0x6C,
    0x6F, 0x72, 0x20, 0x3D, 0x20, 0x72, 0x65, 0x64, 0x20, 0x0A, 0x09, 0x63, 0x6F, 0x6C, 0x6F, 0x72,
    0x20, 0x3D, 0x20, 0x76, 0x65, 0x63, 0x33, 0x28, 0x31, 0x2C, 0x30, 0x2C, 0x30, 0x29, 0x3B, 0x0A,
    0x0A, 0x7D, 0x0A
};
