// Function to handle fetch requests and logging
function sendCommand(url, data, description) {
    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data),
    })
    .then(response => response.text())
    .then(data => console.log(`${description} set to:`, data))
    .catch(error => console.error(`Error setting ${description}:`, error));
}

// Event listener for stepper motor position slider
document.getElementById('stepper-position').addEventListener('input', function() {
    const position = this.value;
    sendCommand(`/moveStepper?position=${position}`, position, 'Stepper position');
});

// Event listener for stepper settings
document.getElementById('stepper-acceleration').addEventListener('change', function() {
    const acceleration = this.value;
    sendCommand(`/setAcceleration?value=${acceleration}`, acceleration, 'Acceleration');
});


document.getElementById('stepper-speed').addEventListener('change', function() {
    const speed = this.value;
    sendCommand(`/setSpeed?value=${speed}`, speed, 'Speed');
});

document.getElementById('submit-password').addEventListener('click', function() {
    const password = document.getElementById('password').value;
    if (password === 'test') {  // Replace 'your_password' with the actual password
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


// Function to add a cat to the list and send data to ESP32
function addCat() {
    const catName = document.getElementById('cat-name').value;
    const foodAmount = document.getElementById('food-amount').value;
    const feedTime = document.getElementById('feeding-time').value;
    const secondFeedTime = document.getElementById('second-feeding-time').value;
    const foodBayLocation = document.getElementById('foodBay-location').value;

    if (!catName || !foodAmount) {
        alert('Please enter both cat name and food amount.');
        return;
    }

    const listItem = document.createElement('li');
    listItem.textContent = `Cat: ${catName}, Food Amount: ${foodAmount} grams, First Feeding Time: ${feedTime}, Second Feeding Time: ${secondFeedTime}, Location: ${foodBayLocation}`;
    document.getElementById('cat-list-items').appendChild(listItem);

    const data = { catName, foodAmount, feedTime, secondFeedTime, foodBayLocation };
    sendCommand('/setFoodBayData', data, 'Food amount for ' + catName);
}

// Event listener for adding a cat
document.getElementById('add-cat').addEventListener('click', addCat);
