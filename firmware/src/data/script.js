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
});
