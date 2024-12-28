.obj files are Wavefront 3D models; they are text files that describe
the geometry of a 3D object.

the .obj file format is a simple data-format that represents 3D geometry alone;
namely, the position of each vertex, the UV position of each texture coordinate
vertex, vertex normals, and the faces that make each polygon defined as a list
of vertices, and texture vertices.
vertices are stored in a counter-clockwise order by default, making explicit
declaration of face normals unnecessary; .obj coordinates have no units, but
.obj files can contain scale information in a human readable comment line.
