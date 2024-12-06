from flask import Flask
import requests

# Initialize Flask app
app = Flask(__name__)

# Replace with the ESP32's IP address
esp32_ip = "http://192.168.144.218"  # Example: "http://192.168.1.100"

# Function to turn the LED on
def turn_led_on():
    url = f"{esp32_ip}/LED=ON"
    response = requests.get(url)
    return response.status_code == 200

# Function to turn the LED off
def turn_led_off():
    url = f"{esp32_ip}/LED=OFF"
    response = requests.get(url)
    return response.status_code == 200

# Route to display the control page
@app.route('/')
def index():
    return """
    <h1>LED Control</h1>
    <p><a href="/turn_on">Turn LED ON</a></p>
    <p><a href="/turn_off">Turn LED OFF</a></p>
    <p><a href="/status">Check LED Status</a></p>
    """

# Route to turn the LED on
@app.route('/turn_on')
def turn_on():
    if turn_led_on():
        return "<h1>LED turned ON</h1><p><a href='/'>Back</a></p>"
    else:
        return "<h1>Failed to turn ON the LED</h1><p><a href='/'>Back</a></p>"

# Route to turn the LED off
@app.route('/turn_off')
def turn_off():
    if turn_led_off():
        return "<h1>LED turned OFF</h1><p><a href='/'>Back</a></p>"
    else:
        return "<h1>Failed to turn OFF the LED</h1><p><a href='/'>Back</a></p>"

# Route to check LED status
@app.route('/status')
def status():
    # You could implement a real check here if your ESP32 reports its current status.
    # For now, let's just assume the LED is "ON" or "OFF"
    led_status = "ON"  # This should be dynamic if your ESP32 reports the status
    return f"<h1>LED Status: {led_status}</h1><p><a href='/'>Back</a></p>"

# Run the app
if __name__ == '__main__':
    app.run(debug=True)
