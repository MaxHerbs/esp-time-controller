from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app, origins=["*"])

@app.route('/')
def home():
    return "Hello, Flask!"

# Define another route
@app.route('/set_wifi_credentials')
def about():
    SSID = request.args.get("SSID")
    password = request.args.get("password")
    print(f"Recieved {SSID}, {password}")
    if SSID and password:
        return jsonify({"status":"success"})
    return jsonify({"status":"failed", "msg":"missing params"})

# Run the application
if __name__ == '__main__':
    app.run(debug=True)