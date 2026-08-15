const express = require("express");
const fs = require("fs");
const path = require("path");
const cors = require("cors");

const app = express();

const PORT = process.env.PORT || 3000;
const DATA_DIR = path.join(__dirname, "data");
const DATA_FILE = path.join(DATA_DIR, "http_data.json");

app.use(cors());
app.use(express.json());

function ensureDataFile() {
  if (!fs.existsSync(DATA_DIR)) {
    fs.mkdirSync(DATA_DIR, { recursive: true });
  }

  if (!fs.existsSync(DATA_FILE)) {
    fs.writeFileSync(DATA_FILE, "[]", "utf8");
  }
}

function readData() {
  ensureDataFile();

  const raw = fs.readFileSync(DATA_FILE, "utf8");

  try {
    return JSON.parse(raw);
  } catch (error) {
    return [];
  }
}

function writeData(data) {
  ensureDataFile();
  fs.writeFileSync(DATA_FILE, JSON.stringify(data, null, 2), "utf8");
}

app.get("/", (req, res) => {
  res.json({
    status: "success",
    message: "IoT HTTP Server is running",
    endpoints: {
      getData: "GET /data",
      postData: "POST /data",
      clearData: "DELETE /data"
    }
  });
});

app.get("/data", (req, res) => {
  const data = readData();

  res.json({
    status: "success",
    count: data.length,
    data: data
  });
});

app.post("/data", (req, res) => {
  const body = req.body;

  const item = {
    sample_id: body.sample_id ?? null,
    temperature: body.temperature ?? null,
    humidity: body.humidity ?? null,
    protocol: body.protocol ?? "HTTP",
    send_time: body.send_time ?? null,
    received_time: new Date().toISOString()
  };

  const data = readData();
  data.push(item);
  writeData(data);

  console.log("====================");
  console.log("NHAN DU LIEU HTTP");
  console.log(item);
  console.log("Da luu vao http_data.json");

  res.status(201).json({
    status: "success",
    message: "HTTP data received",
    data: item
  });
});

app.delete("/data", (req, res) => {
  writeData([]);

  res.json({
    status: "success",
    message: "HTTP data cleared"
  });
});

app.listen(PORT, () => {
  console.log(`HTTP Server running at port ${PORT}`);
});