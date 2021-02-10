const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 3000;

// Cross origin requests
app.use(cors());

// Setting application/json for the body parser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Temp obj for "storage"
let saveData = [];

app.post('/soilmoisture', (req, res) => {
    const packet = req.body;

    // Repack the data for storage
    let packetData = {
        "timestamp": packet.timestamp,
        "sensorId":  packet.sensorId,
        "category":  packet.category,
        "event":     packet.event,
        "payload":   packet.payload
    };
    saveData.push(packetData);

    // Send 201: item created response
    res.status(201).end();
});

app.get('/soilmoisture', (req, res) => {
    if (0 !== saveData.length) {
        // Get the newest piece of data
        // (last item in array)
        res.json(saveData[saveData.length - 1]);
    }
});

app.listen(port, () => {
    console.log(`Listening on http://localhost:${port}`);
})
