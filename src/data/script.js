function update_wifi() {
    let ssid = document.getElementById("ssid_input").value;
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
    let ssid = document.getElementById("ssid_input").value;
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


function update_timezone() {
    const timezone_picker = document.getElementById("timezone-offset");
    const selected_value = timezone_picker.options[timezone_picker.selectedIndex].value;

    if (selected_value === "") {
        console.log("No timezone selected");
        document.getElementById("timezoneResponse").innerHTML = "Please select a timezone from the dropdown";
        return
    }

    let hour = parseInt(selected_value.split(":")[0], 10);
    let minutes = parseInt(selected_value.split(":")[1], 10);

    console.log(selected_value);
    console.log(hour);
    console.log(minutes);




    url = `/set_timezone_details?hours=${hour}&minutes=${minutes}`;
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
                document.getElementById("timezoneResponse").innerHTML = "Timezone details have been updated!";
            } else {
                document.getElementById("timezoneResponse").innerHTML = response;
            }


        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });
}



function reboot() {
    url = "/reboot";
    console.log(url);
    alert("Device will reboot. Discard this window. If properly configured, the light will turn green and the clock will sync within 1 hour.");

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

        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });
}
