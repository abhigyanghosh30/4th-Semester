var cubeRotation = 0.0;
var greyscale = false;

var quit = false;
var programInfo_color;
var score=0;

// document.getElementById("intro-vid").addEventListener('ended',()=>{
//   document.getElementById("intro-vid").style.display = "none";
//   document.getElementById("glcanvas").style.display = "block";
//   main();
// },false);
main();
//
// Start here
//

var c;
var gr;
var left_wall;
var right_wall;
var coins;
var barriers;
var posts;
var jet;
var boots;
var pol;
var trains;

function main() {


  const canvas = document.querySelector('#glcanvas');
  const gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');
  gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
  gl.enable(gl.BLEND);


  c = new cube(gl, [0, 1,1]);
  pol = new police(gl, [0, 1,-10]);
  gr = new ground(gl,[0,0,0]);
  jet = new jetpack(gl, [Math.floor(Math.random()*3-1)*13,1,90]);
  boots = new boot(gl, [Math.floor(Math.random()*3-1)*13,1,97]);
  left_wall = new wall(gl,[20,0,0]);
  right_wall = new wall(gl,[-20,0,0]);
  coins = [];
  for(let i=0;i<=10000;i+=20){
    var x = Math.floor(Math.random()*3-1)*13;
    coins.push(new coin(gl,[x,1,i]));
  } 
  barriers = [];
  for(let i=0;i<10000;i+=80){
    var x = Math.floor(Math.random()*3-1)*13;
    barriers.push(new barrier(gl,[x,1,i]));
  }
  posts = [];
  for(let i=0;i<10000;i+=91){
    var x = Math.floor(Math.random()*3-1)*13;
    posts.push(new post(gl,[x,1,i]));
  }
  trains = new train(gl,[Math.floor(Math.random()*3-1)*13,1,107])
  // If we don't have a GL context, give up now

  if (!gl) {
    alert('Unable to initialize WebGL. Your browser or machine may not support it.');
    return;
  }

  // Vertex shader program

  const vsSource_1 = `
    attribute vec4 aVertexPosition;
    attribute vec4 aVertexColor;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    varying lowp vec4 vColor;

    void main(void) {
      gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
      vColor = aVertexColor;
    }
  `;

  // Fragment shader program

  const fsSource_1 = `
    varying lowp vec4 vColor;

    void main(void) {
      gl_FragColor = vColor;
    }
  `;

  // Initialize a shader program; this is where all the lighting
  // for the vertices and so forth is established.
  const shaderProgram_1 = initShaderProgram(gl, vsSource_1, fsSource_1);

  // Collect all the info needed to use the shader program.
  // Look up which attributes our shader program is using
  // for aVertexPosition, aVevrtexColor and also
  // look up uniform locations.
  const programInfo_1 = {
    program: shaderProgram_1,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram_1, 'aVertexPosition'),
      vertexColor: gl.getAttribLocation(shaderProgram_1, 'aVertexColor'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram_1, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram_1, 'uModelViewMatrix'),
    },
  };

  const vsSource_2 = `
    attribute vec4 aVertexPosition;
    attribute vec2 aTextureCoord;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    varying highp vec2 vTextureCoord;

    void main(void) {
      gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
      vTextureCoord = aTextureCoord;
    }
  `;

  const fsSource_2 = `
    varying highp vec2 vTextureCoord;

    uniform sampler2D uSampler;

    void main(void) {
      gl_FragColor = texture2D(uSampler, vTextureCoord).bbba;
    }
  `;

  const shaderProgram_2 = initShaderProgram(gl, vsSource_2, fsSource_2);

  const programInfo_2 = {
    program: shaderProgram_2,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram_2, 'aVertexPosition'),
      textureCoord: gl.getAttribLocation(shaderProgram_2, 'aTextureCoord'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram_2, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram_2, 'uModelViewMatrix'),
      uSampler: gl.getUniformLocation(shaderProgram_2, 'uSampler'),
    },
  };

  const fsSource_3 = `
    varying highp vec2 vTextureCoord;

    uniform sampler2D uSampler;

    void main(void) {
      gl_FragColor = texture2D(uSampler, vTextureCoord).rgba;
    }
  `;
  const fsSource_4 = `
    varying highp vec2 vTextureCoord;

    uniform sampler2D uSampler;

    void main(void) {
      gl_FragColor = texture2D(uSampler, vTextureCoord).rgba;
      gl_FragColor.r -= 0.2;
      gl_FragColor.g -= 0.2;
      gl_FragColor.b -= 0.2;
    }
  `;

  
  const shaderProgram_3 = initShaderProgram(gl, vsSource_2, fsSource_3);


  const programInfo_3 = {
    program: shaderProgram_3,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram_3, 'aVertexPosition'),
      textureCoord: gl.getAttribLocation(shaderProgram_3, 'aTextureCoord'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram_3, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram_3, 'uModelViewMatrix'),
      uSampler: gl.getUniformLocation(shaderProgram_3, 'uSampler'),
    },
  };

  const shaderProgram_4 = initShaderProgram(gl, vsSource_2, fsSource_4);


  const programInfo_4 = {
    program: shaderProgram_4,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram_4, 'aVertexPosition'),
      textureCoord: gl.getAttribLocation(shaderProgram_4, 'aTextureCoord'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram_4, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram_4, 'uModelViewMatrix'),
      uSampler: gl.getUniformLocation(shaderProgram_4, 'uSampler'),
    },
  };
  programInfo_color = programInfo_4;
  // Here's where we call the routine that builds all the
  // objects we'll be drawing.
  //const buffers

  var then = 0;

  // Draw the scene repeatedly
  function render(now) {
    now *= 0.001;  // convert to seconds
    const deltaTime = now - then;
    then = now;
    drawScene(gl, programInfo_1,programInfo_2,programInfo_3,programInfo_4);
    tick_input();
    tick_elements(gl);
    detect_collisions();
    if(quit==true){
      endscene(false);
      return;
    }
    if(c.pos[2]==10000){
      endscene(true);
      return;
    }

    requestAnimationFrame(render);
  }
  requestAnimationFrame(render);
}

//
// Draw the scene.
//
function drawScene(gl, programInfo_1,programInfo_2, programInfo_3,programInfo_4) {
  gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
  gl.clearDepth(1.0);                 // Clear everything
  gl.enable(gl.DEPTH_TEST);           // Enable depth testing
  gl.depthFunc(gl.LEQUAL);            // Near things obscure far things

  // Clear the canvas before we start drawing on it.

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  // Create a perspective matrix, a special matrix that is
  // used to simulate the distortion of perspective in a camera.
  // Our field of view is 45 degrees, with a width/height
  // ratio that matches the display size of the canvas
  // and we only want to see objects between 0.1 units
  // and 100 units away from the camera.

  const fieldOfView = 45 * Math.PI / 180;   // in radians
  const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
  const zNear = 0.1;
  const zFar = 500.0;
  const projectionMatrix = mat4.create();

  // note: glmatrix.js always has the first argument
  // as the destination to receive the result.
  mat4.perspective(projectionMatrix,
                   fieldOfView,
                   aspect,
                   zNear,
                   zFar);

  // Set the drawing position to the "identity" point, which is
  // the center of the scene.
    var cameraMatrix = mat4.create();
    mat4.translate(cameraMatrix, cameraMatrix, [0, c.jet==true?20:10 ,c.pos[2]-40]);
    var cameraPosition = [
      cameraMatrix[12],
      cameraMatrix[13],
      cameraMatrix[14],
    ];

    var up = [0, 1, 0];

    mat4.lookAt(cameraMatrix, cameraPosition, [0,0,c.pos[2]], up);

    var viewMatrix = cameraMatrix;//mat4.create();

    //mat4.invert(viewMatrix, cameraMatrix);

    var viewProjectionMatrix = mat4.create();

    mat4.multiply(viewProjectionMatrix, projectionMatrix, viewMatrix);  
  if(c.pos[2]%100==1)
  {
    if(programInfo_color == programInfo_3)
      programInfo_color = programInfo_4;
    else
      programInfo_color = programInfo_3;
    console.log(programInfo_color);
  }
    

  gr.drawCube(gl, viewProjectionMatrix, programInfo_2);
  left_wall.drawCube(gl, viewProjectionMatrix, greyscale?programInfo_2:programInfo_color);
  right_wall.drawCube(gl, viewProjectionMatrix,greyscale?programInfo_2:programInfo_color);
  trains.drawCube(gl, viewProjectionMatrix, greyscale?programInfo_2:programInfo_3);
  for(var j in coins){
    if(coins[j].pos[2] < c.pos[2]-30)
    coins.shift();
    else if(coins[j].pos[2]-c.pos[2]<=200)
    // if(coins[j].display==true)
    coins[j].drawCube(gl,viewProjectionMatrix,greyscale?programInfo_2:programInfo_3);
    else
    break;
  }
  for(var i in barriers){
    if(barriers[i].pos[2] < c.pos[2]-30)
    barriers.shift();
    else if(barriers[i].pos[2]-c.pos[2]<=200)
    barriers[i].drawCube(gl,viewProjectionMatrix, greyscale?programInfo_2:programInfo_3);
    else
    break;
  }
  for(var i in posts){
    if(posts[i].pos[2] < c.pos[2]-30)
    posts.shift();
    else if(posts[i].pos[2]-c.pos[2]<=200)
    posts[i].drawCube(gl,viewProjectionMatrix,greyscale?programInfo_2:programInfo_3);
    else
    break;
  }
  jet.drawCube(gl,viewProjectionMatrix,greyscale?programInfo_2:programInfo_3);
  boots.drawCube(gl,viewProjectionMatrix,greyscale?programInfo_2:programInfo_3);
  pol.drawCube(gl, viewProjectionMatrix, greyscale?programInfo_2:programInfo_3);
  c.drawCube(gl, viewProjectionMatrix, greyscale?programInfo_2:programInfo_3);
}

//
// Initialize a shader program, so WebGL knows how to draw our data
//
function initShaderProgram(gl, vsSource, fsSource) {
  const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
  const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

  // Create the shader program

  const shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);

  // If creating the shader program failed, alert

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert('Unable to initialize the shader program: ' + gl.getProgramInfoLog(shaderProgram));
    return null;
  }

  return shaderProgram;
}

//
// creates a shader of the given type, uploads the source and
// compiles it.
//
function loadShader(gl, type, source) {
  const shader = gl.createShader(type);

  // Send the source to the shader object

  gl.shaderSource(shader, source);

  // Compile the shader program

  gl.compileShader(shader);

  // See if it compiled successfully

  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
    return null;
  }

  return shader;
}

function tick_input(){
    document.onkeypress = function(e){
      if('a' == e.key){
        c.pos[0] = c.pos[0]==13?13:c.pos[0]+13;
      }
      if('d' == e.key){
        c.pos[0] = c.pos[0]==-13?-13:c.pos[0]-13;
      }
      if('w' == e.key){
        if(c.pos[1]==1)
        {
          console.log(c.jump);
          if(c.jump==false)
            c.speed[1] = 1;
          if(c.jump==true)
            c.speed[1] = 2;
          }
      }
      if('s' == e.key){
        if(c.pos[1]==1){
          c.duck=true;
          c.speed[1]=-0.5;
        }
      }
      if('c' == e.key){
        greyscale = !greyscale;
      }
    }
}

function tick_elements(gl){
  c.tick();
  pol.setPosition([c.pos[0],1,c.pos[2]]);
  pol.tick();
}

//
// Initialize a texture and load an image.
// When the image finished loading copy it into the texture.
//
function loadTexture(gl, url) {
  const texture = gl.createTexture();
  gl.bindTexture(gl.TEXTURE_2D, texture);

  // Because images have to be download over the internet
  // they might take a moment until they are ready.
  // Until then put a single pixel in the texture so we can
  // use it immediately. When the image has finished downloading
  // we'll update the texture with the contents of the image.
  const level = 0;
  const internalFormat = gl.RGBA;
  const width = 1;
  const height = 1;
  const border = 0;
  const srcFormat = gl.RGBA;
  const srcType = gl.UNSIGNED_BYTE;
  const pixel = new Uint8Array([0, 0, 255, 255]);  // opaque blue
  gl.texImage2D(gl.TEXTURE_2D, level, internalFormat,
                  width, height, border, srcFormat, srcType,
                  pixel);

  const image = new Image();
  
  image.onload = function() {
      gl.bindTexture(gl.TEXTURE_2D, texture);
      gl.texImage2D(gl.TEXTURE_2D, level, internalFormat,
                  srcFormat, srcType, image);

      // WebGL1 has different requirements for power of 2 images
      // vs non power of 2 images so check if the image is a
      // power of 2 in both dimensions.
      if (isPowerOf2(image.width) && isPowerOf2(image.height)) {
          // Yes, it's a power of 2. Generate mips.
          gl.generateMipmap(gl.TEXTURE_2D);
      } else {
          // No, it's not a power of 2. Turn off mips and set
          // wrapping to clamp to edge
          gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
          gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
          gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      }
  };

  image.src = url;

  return texture;
}

function isPowerOf2(value) {
  return (value & (value - 1)) == 0;
}

function detect_collisions(){
  for(var j in coins){
    if(coins[j].pos[0]==c.pos[0] && coins[j].pos[1]==c.pos[1] && coins[j].pos[2]==c.pos[2])
    {
      coins[j].display=false;
      score++;
      document.getElementById("score").innerHTML=score;
    }
    if(coins[j].pos[2]>c.pos[2]+10)
      break;
  }
  for(var i in barriers){
    if(barriers[i].pos[0]==c.pos[0] &&  barriers[i].pos[2]==c.pos[2])
    {
      if(c.pos[1]==barriers[i].pos[1]){
        pol.follow=true;
        pol.counter = c.pos[2]+400;
        console.log("bring forward");
      }
      else if(c.pos[1]-barriers[i].pos[1]<=4.5 && c.pos[1]-barriers[i].pos[1]>0)
        quit=true;
    }
    if(barriers[i].pos[2]>c.pos[2]+10)
      break;
  }
  for(var i in posts){
    if(posts[i].pos[0]==c.pos[0] && c.pos[1]-posts[i].pos[1]<=2 && posts[i].pos[2]==c.pos[2])
    {
      quit=true;
    }
    if(barriers[i].pos[2]>c.pos[2]+10)
      break;
  }
  if(jet.pos[2]==c.pos[2] && jet.pos[1]==c.pos[1] && jet.pos[0]==c.pos[0]){
    jet.display = false;
    c.jet = true;
    c.counter = jet.pos[2]+200;
    for(var i=1;i<=10;i++){
      coins[i].pos[1] = 10;
    }
  }
  if(boots.pos[2]==c.pos[2] && boots.pos[1]==c.pos[1] && boots.pos[0]==c.pos[0]){
    boots.display = false;
    c.jump = true;
    c.jump_c = boots.pos[2]+200;
  }
  if(jet.pos[2]<c.pos[2]-30){
    jet.pos[2] += 997;
    jet.pos[0] = Math.floor(Math.random()*3-1)*13;
    jet.display=true;
  }
  if(boots.pos[2]<c.pos[2]-30){
    boots.pos[2] += 1007;
    boots.pos[0] = Math.floor(Math.random()*3-1)*13;
    boots.display=true;
  }
  if(trains.pos[2]-2==c.pos[2] && trains.pos[0]==c.pos[0] && c.pos[1] - trains.pos[1]<=4.5){
    quit=true;
  }
  else if(trains.pos[2]-c.pos[2]<=1 && trains.pos[0]==c.pos[0]){

  }
  if(trains.pos[2]<c.pos[2]-30){
    trains.pos[2] += 517
    trains.pos[0] = Math.floor(Math.random()*3-1)*13;
  }
}

function endscene(success){
  document.getElementById("glcanvas").style.display = "none";
  if(success==true){
    document.getElementById("finish").style.display = "block";
  }
  if(success==false){
    document.getElementById("die").style.display = "block";
  }
}