document.addEventListener("DOMContentLoaded", function() {

    // Function to send data
    function sendData() {
        const foodBayModules = [];
  
        for (let i = 1; i <= 3; i++) {
            const moduleData = {
                catName: document.getElementById(`catName${i}`).value,
                foodQuantity: parseInt(document.getElementById(`foodQuantity${i}`).value, 10),
                time1: document.getElementById(`time${i}1`).value,
                time2: document.getElementById(`time${i}2`).value,
                active: document.getElementById(`active${i}`).checked
            };
            foodBayModules.push(moduleData);
        }
  
        const data = { foodBayModules };
        console.log('Sending data:', JSON.stringify(data)); // Log data to console
  
        fetch('/postdata', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(data),
        })
        .then(response => response.json())
        .then(result => console.log('Module data update success:', result))
        .catch(error => console.error('Module data update error:', error));
    }
  
    // Function to fetch data from the server and populate the form
    function fetchData() {
        fetch('/getdata', {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json'
            }
        }).then(response => response.json())
            .then(data => populateForm(data.foodBayModules))
            .catch(error => console.error('Error fetching data:', error));
    }
  
    // Function to populate the form with fetched data
    function populateForm(foodBayModules) {
        foodBayModules.forEach((moduleData, index) => {
            const i = index + 1;
            document.getElementById(`catName${i}`).value = moduleData.catName;
            document.getElementById(`foodQuantity${i}`).value = moduleData.foodQuantity;
            document.getElementById(`time${i}1`).value = moduleData.time1;
            document.getElementById(`time${i}2`).value = moduleData.time2;
            document.getElementById(`active${i}`).checked = moduleData.active;
        });
    }
  
    // Function to set up event listeners for form inputs
    function setupEventListeners() {
        for (let i = 1; i <= 3; i++) {
            document.getElementById(`catName${i}`).addEventListener('change', sendData);
            document.getElementById(`foodQuantity${i}`).addEventListener('change', sendData);
            document.getElementById(`time${i}1`).addEventListener('change', sendData);
            document.getElementById(`time${i}2`).addEventListener('change', sendData);
            document.getElementById(`active${i}`).addEventListener('change', sendData);
        }
    }
  
    // Fetch data when the document is fully loaded
    fetchData();
    setupEventListeners();
  });
  