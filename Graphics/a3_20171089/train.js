/// <reference path="webgl.d.ts" />

let train = class {
    constructor(gl, pos) {
        this.positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer);
        this.speed = [0,0,-1];
        this.jet = false;
        this.counter = 0;
        this.jump=false;
        this.positions = [
            // Front face
            -3.0, -1.0, 2.0,
            3.0, -1.0, 2.0,
            3.0, 6.0, 2.0,
            -3.0, 6.0, 2.0,
            //Back Face
            -3.0, -1.0, -2.0,
            3.0, -1.0, -2.0,
            3.0, 6.0, -2.0,
            -3.0, 6.0, -2.0,
            //Top Face
            -3.0, 6.0, -2.0,
            3.0, 6.0, -2.0,
            3.0, 6.0, 2.0,
            -3.0, 6.0, 2.0,
            //Bottom Face
            -3.0, -1.0, -2.0,
            3.0, -1.0, -2.0,
            3.0, -1.0, 2.0,
            -3.0, -1.0, 2.0,
            //Left Face
            -3.0, -1.0, -2.0,
            -3.0, 6.0, -2.0,
            -3.0, 6.0, 2.0,
            -3.0, -1.0, 2.0,
            //Right Face
            3.0, -1.0, -2.0,
            3.0, 6.0, -2.0,
            3.0, 6.0, 2.0,
            3.0, -1.0, 2.0,
        ];

        this.rotation = 0;

        this.pos = pos;

        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);
        

        // Build the element array buffer; this specifies the indices
        // into the vertex arrays for each face's vertices.

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

        // This array defines each face as two triangles, using the
        // indices into the vertex array to specify each triangle's
        // position.

        const indices = [
            0,  1,  2,      0,  2,  3,    // front
            4,  5,  6,      4,  6,  7,    // back
            8,  9,  10,     8,  10, 11,   // top
            12, 13, 14,     12, 14, 15,   // bottom
            16, 17, 18,     16, 18, 19,   // right
            20, 21, 22,     20, 22, 23,   // left
        ];

        // Now send the element array to GL

        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER,
            new Uint16Array(indices), gl.STATIC_DRAW);

        // Load texture
        this.texture_front = loadTexture(gl, 'train_front.png');
        this.texture_side = loadTexture(gl, 'train_side.png');
        
        const textureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);

        const textureCoordinates = [
            // Front
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Back
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Top
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Bottom
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Left
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
            // Right
            1.0,  1.0,
            0.0,  1.0,
            0.0,  0.0,
            1.0,  0.0,
        ];

        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates),
                gl.STATIC_DRAW);
            
        this.buffer = {
            position: this.positionBuffer,
            textureCoord: textureCoordBuffer,
            indices: indexBuffer,
        }

    }

    setPosition(pos){
        this.pos = pos;
    }

    tick(){
        this.pos[0] += this.speed[0];
        this.pos[1] += this.speed[1]; 
        this.pos[2] += this.speed[2];
    }

    drawCube(gl, projectionMatrix, programInfo) {
        const modelViewMatrix = mat4.create();
        mat4.translate(
            modelViewMatrix,
            modelViewMatrix,
            this.pos
        );
        
        //this.rotation += Math.PI / (((Math.random()) % 100) + 50);

        mat4.rotate(modelViewMatrix,
            modelViewMatrix,
            this.rotation,
            [1, 1, 1]);

        {
            const numComponents = 3;
            const type = gl.FLOAT;
            const normalize = false;
            const stride = 0;
            const offset = 0;
            gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.position);
            gl.vertexAttribPointer(
                programInfo.attribLocations.vertexPosition,
                numComponents,
                type,
                normalize,
                stride,
                offset);
            gl.enableVertexAttribArray(
                programInfo.attribLocations.vertexPosition);
        }

        // Tell WebGL how to pull out the colors from the color buffer
        // into the vertexColor attribute.
        {
            const numComponents = 2;
            const type = gl.FLOAT;
            const normalize = false;
            const stride = 0;
            const offset = 0;
            gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.textureCoord);
            gl.vertexAttribPointer(
                programInfo.attribLocations.textureCoord,
                numComponents,
                type,
                normalize,
                stride,
                offset);
            gl.enableVertexAttribArray(
                programInfo.attribLocations.textureCoord);
        }

        // Tell WebGL which indices to use to index the vertices
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffer.indices);

        // Tell WebGL to use our program when drawing

        gl.useProgram(programInfo.program);

        // Set the shader uniforms

        gl.uniformMatrix4fv(
            programInfo.uniformLocations.projectionMatrix,
            false,
            projectionMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.modelViewMatrix,
            false,
            modelViewMatrix);
        // Specify the texture to map onto the faces.

        // Tell WebGL we want to affect texture unit 0
        gl.activeTexture(gl.TEXTURE1);

        // Bind the texture to texture unit 0
        gl.bindTexture(gl.TEXTURE_2D, this.texture_side);

        // Tell the shader we bound the texture to texture unit 0
        gl.uniform1i(programInfo.uniformLocations.uSampler, 1);

        {
            const vertexCount = 24;
            const type = gl.UNSIGNED_SHORT;
            const offset = 12 * 2;
            gl.drawElements(gl.TRIANGLES, vertexCount, type, offset);
        }

        // Tell WebGL we want to affect texture unit 0
        gl.activeTexture(gl.TEXTURE0);

        // Bind the texture to texture unit 0
        gl.bindTexture(gl.TEXTURE_2D, this.texture_front);

        // Tell the shader we bound the texture to texture unit 0
        gl.uniform1i(programInfo.uniformLocations.uSampler, 0);

        {
            const vertexCount = 12;
            const type = gl.UNSIGNED_SHORT;
            const offset = 0;
            gl.drawElements(gl.TRIANGLES, vertexCount, type, offset);
        }

    }
};