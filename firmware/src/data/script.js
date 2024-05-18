// Function to handle fetch requests and logging
function sendStepperCommand(url, data, description) {
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

// Function to add a cat to the list and send data to ESP32
function addCat() {
    const catName = document.getElementById('cat-name').value;
    const foodAmount = document.getElementById('food-amount').value;

    if (!catName || !foodAmount) {
        alert('Please enter both cat name and food amount.');
        return;
    }

    const listItem = document.createElement('li');
    listItem.textContent = `Cat: ${catName}, Food Amount: ${foodAmount} grams`;
    document.getElementById('cat-list-items').appendChild(listItem);

    const data = { catName, foodAmount };
    sendStepperCommand('/setFoodAmount', data, 'Food amount for ' + catName);
}

// Event listener for adding a cat
document.getElementById('add-cat').addEventListener('click', addCat);
