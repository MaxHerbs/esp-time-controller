function update_timezone() {
    const continentSelect = document.getElementById("continent");
    const citySelect = document.getElementById("city");

    const continent = continentSelect.options[continentSelect.selectedIndex].value;
    const city = citySelect.options[citySelect.selectedIndex].value;


    if (continent === "" || city === "") {
        console.log("No timezone selected");
        document.getElementById("timezoneResponse").innerHTML = "Please select a continent and city from the dropdowns";
        return
    }

    console.log(continent);
    console.log(city);



    url = `/set_timezone_details?continent=${continent}&city=${city}`;
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


