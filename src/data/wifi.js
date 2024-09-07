function update_wifi() {
    const ssid_select = document.getElementById("ssid");
    const ssid = ssid_select.options[ssid_select.selectedIndex].value;
    let password = document.getElementById("password_input").value;

    if (ssid.length < 1 || ssid.length > 30) {
        console.log("SSID does not fit length constraints");
    }

    if (password.length < 1 || password.length > 30) {
        console.log("Password does not fit length constraints");
    }

    base_url = "http://127.0.0.1:5000"
    url = `/set_wifi_credentials?ssid=${ssid}&password=${password}`;
    console.log(url);


    fetch(url)
        .then(response => {
            // Check if the response is successful (status code 200-299)
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            // Parse the response body as JSON
            return response.text();
        })
        .then(response => {
            // Handle the parsed data
            console.log(response);

            if (response == "Success") {
                document.getElementById("wifiResponse").innerHTML = "Wifi credentials have been updated!";
            } else {
                document.getElementById("wifiResponse").innerHTML = response;
            }


        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });


}


function verify_wifi() {
    const ssid_select = document.getElementById("ssid");
    const ssid = ssid_select.options[ssid_select.selectedIndex].value;
    let password = document.getElementById("password_input").value;

    if (ssid.length < 1 || ssid.length > 30) {
        console.log("SSID does not fit length constraints");
    }

    if (password.length < 1 || password.length > 30) {
        console.log("Password does not fit length constraints");
    }

    base_url = "http://127.0.0.1:5000"
    url = `/verify_wifi_credentials?ssid=${ssid}&password=${password}`;
    console.log(url);


    
    document.getElementById("wifiResponse").innerHTML = "Attempting to verify credentials...";
    fetch(url)
        .then(response => {
            // Check if the response is successful (status code 200-299)
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            // Parse the response body as JSON
            return response.text();
        })
        .then(response => {
            // Handle the parsed data
            console.log(response);

            if (response == "Success") {
                document.getElementById("wifiResponse").innerHTML = "Wifi credentials verified!";
            } 
            if (response == "Failure") {
                document.getElementById("wifiResponse").innerHTML = "Failed to validate wifi credentials";
            }


        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });


}



function get_available_wifi(){
    url = `/get_available_wifi`;
    console.log(url);


    
    fetch(url)
        .then(response => {
            // Check if the response is successful (status code 200-299)
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            // Parse the response body as JSON
            return response.text();
        })
        .then(response => {
            // Handle the parsed data
            console.log(response);
            const ssid_select = document.getElementById("ssid");
            const ssid_list = response.split("\n");

            while (ssid_select.options.length > 0) {
                ssid_select.remove(0);
            }

            let defaultOption = document.createElement("option");
            defaultOption.value = "";
            defaultOption.disabled = true;
            defaultOption.selected = true;
            defaultOption.textContent = "Select a network";
            ssid_select.appendChild(defaultOption);



            ssid_list.forEach(ssid => {
                console.log(ssid);
                let option = document.createElement("option");
                option.value = ssid;
                option.text = ssid;
                ssid_select.appendChild(option);
            });

        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });
}