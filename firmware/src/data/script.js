// Function to handle fetch requests and logging
function sendStepperCommand(url, value, description) {
    fetch(url, { method: 'POST' })
    .then(response => response.text())
    .then(data => console.log(`${description} set to:`, value))
    .catch(error => console.error(`Error setting ${description}:`, error));
}

// Event listener for stepper motor position slider
document.getElementById('stepper-position').addEventListener('input', function() {
    const position = this.value;
    sendStepperCommand(`/moveStepper?position=${position}`, position, 'Stepper position');
});

// Event listener for stepper settings
document.getElementById('stepper-acceleration').addEventListener('change', function() {
    const acceleration = this.value;
    sendStepperCommand(`/setAcceleration?value=${acceleration}`, acceleration, 'Acceleration');
});

document.getElementById('stepper-speed').addEventListener('change', function() {
    const speed = this.value;
    sendStepperCommand(`/setSpeed?value=${speed}`, speed, 'Speed');

document.getElementById('submit-password').addEventListener('click', function() {
    const password = document.getElementById('password').value;
    if (password === 'your_password') {  // Replace 'your_password' with the actual password
        document.getElementById('password-section').style.display = 'none';
        document.getElementById('setup-section').style.display = 'block';
    } else {
        document.getElementById('password-error').style.display = 'block';
    }
});

document.getElementById('pin-config-form').addEventListener('submit', function(event) {
    event.preventDefault();
    const sdaPin = document.getElementById('sdaPin').value;
    const sclPin = document.getElementById('sclPin').value;
    const stepPin = document.getElementById('stepPin').value;
    const dirPin = document.getElementById('dirPin').value;
    
    fetch('/updatePins', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ sdaPin, sclPin, stepPin, dirPin }),
    })
    .then(response => response.text())
    .then(data => alert('Pins updated successfully!'))
    .catch(error => console.error('Error updating pins:', error));
});
