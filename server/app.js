const express = require('express')
const fs = require('fs')
const path = require('path')
const formidable = require('formidable')

const app = express()
const port = 3000

app.use(express.json({limit: '50mb'}))
app.use(express.urlencoded({ extended: true, limit: '50mb' }))

app.use(express.static(__dirname));


app.get('/', (req, res) => {
  // clear uploads folder on startup
  try {
    fs.unlinkSync(__dirname + '/uploads/image.jpg')
    fs.unlinkSync(__dirname + '/pred.jpg')
    console.log("deleted image.jpg")
  } catch(err) {
    console.log("/uploads has no image.jpg to remove")
  }
  res.sendFile(__dirname + '/index.html')
})

// grab uploaded file
app.post('/upload', (req, res) => {
  const form = new formidable.IncomingForm();
  form.parse(req);

  form.on('fileBegin', (name, file) => {
      file.path = __dirname + '/uploads/image.jpg';
  });

  form.on('file', (name, file) => {
      console.log('Uploaded ' + file.name);
  });

  res.sendFile(__dirname + '/index.html');
})

// send file to client
app.get('/image', (req, res) => {

  // check if the image was uploaded and exists
  fs.stat(__dirname + '/uploads/image.jpg', (err, stat) => {
    if (err == null) {
      console.log('sending image to pyclient')
      res.sendFile(__dirname + '/uploads/image.jpg')
    } else if (err.code === 'ENOENT') {
      res.send('');
    }
  })
  
})


app.post('/result', (req, res) => {
  // delete image once prediction is sent back
  try {
    fs.unlinkSync(__dirname + '/uploads/image.jpg')
    console.log("deleted image.jpg")
  } catch(err) {
    console.log("/uploads has no image.jpg to remove")
  }

  console.log("server received prediction")
  
  fs.writeFile("pred.jpg", Buffer.from(req.body.pred, 'base64'), 'base64', (err) => {
    if (err) {
      console.log(err)
    }
  });
  
  res.end()
})

app.get('/getImage', (req, res) => {
  fs.stat(__dirname + '/pred.jpg', (err, stat) => {
    if (err == null) {
      console.log('sending image to html')

      // delete old input image
      try {
        fs.unlinkSync(__dirname + '/uploads/image.jpg')
        console.log("deleted image.jpg after sending to html")
      } catch(err) {
        console.log("/uploads has no image.jpg to remove")
      }

      res.send('pred.jpg')
    } else if (err.code === 'ENOENT') {
      res.end();
    }
  })
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})