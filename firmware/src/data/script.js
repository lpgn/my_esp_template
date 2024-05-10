// JavaScript to toggle a device connected to the ESP
document.getElementById('toggleDevice').addEventListener('click', function() {
    fetch('/toggle', { method: 'POST' })
    .then(response => response.text())
    .then(data => alert('Device toggled. Server says: ' + data))
    .catch(error => console.error('Error toggling device:', error));
});
