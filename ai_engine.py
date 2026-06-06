import time
import firebase_admin
from firebase_admin import credentials, db

cred = credentials.Certificate("serviceAccountKey.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://your-project.firebaseio.com/'
})

def get_temp():
    ref = db.reference("/sensor/temperature")
    return ref.get()

def set_fan(status):
    db.reference("/ai/fan_status").set(status)

while True:
    temp = get_temp()
    print("Temperature:", temp)

    # 🧠 AI Decision Logic
    if temp is not None:
        if temp > 30:
            set_fan("ON")
        else:
            set_fan("OFF")

    time.sleep(2)
