const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);

// Serve static files from the "public" directory
app.use(express.static('public'));

// Define a route for the homepage
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

// Socket.IO event handling
io.on('connection', (socket) => {
  console.log('A user connected');

  // Handle a custom event from the client
  socket.on('chat message', (message) => {
    console.log('Received message:', message);
    io.emit('chat message', message); // Broadcast the message to all connected clients
  });

  // Handle disconnection
  socket.on('disconnect', () => {
    console.log('A user disconnected');
  });
});

// Start the server
const port = process.env.PORT || 3000;
http.listen(port, () => {
  console.log(`Server is listening on port ${port}`);
});
