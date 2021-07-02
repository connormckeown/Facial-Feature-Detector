# CMPT383 Project
## Sketching a Plan
- Topic idea: Image classifier that decides if the person in an uploaded photo is wearing a mask or not
- The three programming languages will include,
-- The server code will be written in **JavaScript** with Node.js
-- The code for the client that interacts with the Node.js server will be written in **Python**
-- The program which the Python client calls to do calculations will be written in **C++**
- Inter-language communication methods,
-- The Python client will call C++ functions through the foreign function interface SWIG
-- The Python client sends an HTTP request to the Node.js server and recieves the image the user uploads
- The deployment will be with **Docker Compose + Containers**