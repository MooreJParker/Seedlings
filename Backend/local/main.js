// Set the up http REST connection
const http = require('http');
const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/soilmoisture',
    method: 'POST',
    headers: {
        'Content-Type': 'application/json'
    }
};

// Set up the serial connection
const SerialPort = require('serialport');
const port = new SerialPort('COM3',
    {
        baudRate: 9600
    });

// Receive serial data, unpack, repack into JSON, and send
// over REST
port.on('data', function(dataBuff) {
    // Read the data out of the buffer and place it in the
    // object to send over HTTP
    const sendData = JSON.stringify({
        "timestamp": Date.now(),
        "sensorId":  dataBuff.readUInt8(0),
        "category":  dataBuff.readUInt8(1),
        "event":     dataBuff.readUInt8(2),
        "payload":   dataBuff.readUint16LE(3)
    });

    // Send the request
    const req = http.request(options, res => {
        // Additonal error handling occurs here
        console.log(`statusCode: ${res.statusCode}`);
    })
    req.write(sendData);
    req.end();
});
