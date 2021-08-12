const express = require('express')
const fs = require('fs')
const path = require('path')
const formidable = require('formidable')

const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html')
})

// grab uploaded file
app.post('/upload', (req, res) => {
  const form = new formidable.IncomingForm();
  form.parse(req);

  form.on('fileBegin', (name, file) => {
      file.path = __dirname + '/uploads/' + file.name;
  });

  form.on('file', (name, file) => {
      console.log('Uploaded ' + file.name);
  });

  res.sendFile(__dirname + '/index.html');
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})