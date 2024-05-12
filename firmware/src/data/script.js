let direction = false;  // false for one direction, true for the other

document.getElementById('toggle').addEventListener('click', function() {
    fetch('/toggleStepper', { method: 'POST' }) // Changed endpoint to toggleStepper
    .then(response => response.text())
    .then(data => alert('Stepper direction will be toggled. Server says: ' + data))
    .catch(error => console.error('Error toggling stepper direction:', error));
});

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

document.getElementById('steps-per-mm').addEventListener('change', function() {
    const stepsPerMM = this.value;
    fetch(`/setStepsPerMM?value=${stepsPerMM}`, { method: 'POST' })
    .then(response => response.text())
    .then(data => console.log('Steps per mm set to:', stepsPerMM))
    .catch(error => console.error('Error setting steps per mm:', error));
});
