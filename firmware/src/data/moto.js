document.addEventListener("DOMContentLoaded", () => {
    document.getElementById('stepper-position').addEventListener('input', () => {
        const position = this.value;
        sendCommand(`/moveStepper?position=${position}`, position, 'Stepper position');
    });

    document.getElementById('stepper-acceleration')?.addEventListener('change', () => {
        const acceleration = this.value;
        sendCommand(`/setAcceleration?value=${acceleration}`, acceleration, 'Acceleration');
    });

    // Stepper speed
    document.getElementById('stepper-speed')?.addEventListener('change', () => {
        const speed = this.value;
        sendCommand(`/setSpeed?value=${speed}`, speed, 'Speed');
    });

    // Password submit
    document.getElementById('submit-password')?.addEventListener('click', () => {
        const password = document.getElementById('password').value;
        if (password === 'test') {
            document.getElementById('password-section').style.display = 'none';
            document.getElementById('setup-section').style.display = 'block';
        } else {
            document.getElementById('password-error').style.display = 'block';
        }
    });

    // Pin configuration form
    document.getElementById('pin-config-form')?.addEventListener('submit', (event) => {
        event.preventDefault();
        const sdaPin = document.getElementById('sdaPin').value;
        const sclPin = document.getElementById('sclPin').value;
        const stepPin = document.getElementById('stepPin').value;
        const dirPin = document.getElementById('dirPin').value;

        fetch('/postdataPins', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ sdaPin, sclPin, stepPin, dirPin }),
        })
            .then(response => response.text())
            .then(() => alert('Pins updated successfully!'))
            .catch(error => console.error('Error updating pins:', error));
    });
});
