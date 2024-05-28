function loadData() {
  fetch('/data').then(response => response.json()).then(data => {
    let table = document.getElementById('data-table');
    for (let module in data) {
      let row = document.createElement('tr');
      row.innerHTML = `
        <td>${module}</td>
        <td><input type='text' id='${module}_cat_name' value='${data[module].cat_name}' onchange='updateData("${module}", "cat_name", this.value)' /></td>
        <td><input type='number' id='${module}_amount_food' value='${data[module].amount_food}' onchange='updateData("${module}", "amount_food", this.value)' /></td>
        <td><input type='time' id='${module}_time1' value='${data[module].time1}' onchange='updateData("${module}", "time1", this.value)' /></td>
        <td><input type='time' id='${module}_time2' value='${data[module].time2}' onchange='updateData("${module}", "time2", this.value)' /></td>
        <td><input type='checkbox' id='${module}_active' ${data[module].active ? 'checked' : ''} onchange='updateData("${module}", "active", this.checked)' /></td>
      `;
      table.appendChild(row);
    }
  });
}

function updateData(module, key, value) {
  fetch('/postdata', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({ module: module, key: key, value: value })
  }).then(response => response.text()).then(response => {
    console.log(response);
  });
}

window.onload = loadData;
