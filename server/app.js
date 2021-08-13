const express = require('express')
const fs = require('fs')
const path = require('path')
const formidable = require('formidable')

const app = express()
const port = 3000

// clear uploads folder on startup
try {
  fs.unlinkSync(__dirname + '/uploads/image.jpg')
  //file removed
} catch(err) {
  console.log("/uploads has no image.jpg to remove")
}

app.get('/', (req, res) => {
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
      // console.log("image.jpg does not exist")
      res.send('no image')
    }
  })
  
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})