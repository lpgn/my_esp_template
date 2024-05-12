let direction = false;  // false for one direction, true for the other

// Event listener for stepper motor position slider
document.getElementById('stepper-position').addEventListener('input', function() {
    const position = this.value;
    fetch(`/moveStepper?position=${position}`, { method: 'POST' })
    .then(response => response.text())
    .then(data => console.log('Stepper moved to position:', position))
    .catch(error => console.error('Error moving stepper:', error));
});

// Event listeners for stepper settings
document.getElementById('stepper-acceleration').addEventListener('change', function() {
    const acceleration = this.value;
    fetch(`/setAcceleration?value=${acceleration}`, { method: 'POST' })
    .then(response => response.text())
    .then(data => console.log('Acceleration set to:', acceleration))
    .catch(error => console.error('Error setting acceleration:', error));
});

document.getElementById('stepper-speed').addEventListener('change', function() {
    const speed = this.value;
    fetch(`/setSpeed?value=${speed}`, { method: 'POST' })
    .then(response => response.text())
    .then(data => console.log('Speed set to:', speed))
    .catch(error => console.error('Error setting speed:', error));
});

