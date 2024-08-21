import json

wifi = {
    "ssid": "temp",
    "password": "temp"
}

timezone = {
    "hours": 1,
    "minutes":30
}

x = {
    "wifi": wifi,
    "timezone": timezone
}

json_str = json.dumps(x)
print(json_str)
