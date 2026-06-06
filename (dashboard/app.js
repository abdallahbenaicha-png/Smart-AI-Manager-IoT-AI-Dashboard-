var firebaseConfig = {
  apiKey: "XXX",
  databaseURL: "https://your-project.firebaseio.com/"
};

firebase.initializeApp(firebaseConfig);
var db = firebase.database();

db.ref("/sensor/temperature").on("value", (snap) => {
  document.getElementById("temp").innerHTML = snap.val() + " °C";
});

db.ref("/ai/fan_status").on("value", (snap) => {
  document.getElementById("fan").innerHTML = snap.val();
});
