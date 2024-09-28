// ####################################################
// #################### General ###################### 
// ####################################################


const timezone_dict = {
	"Africa":["Abidjan","Accra","Addis_Ababa","Algiers","Asmara","Asmera","Bamako","Bangui","Banjul","Bissau","Blantyre","Brazzaville","Bujumbura","Cairo","Casablanca","Ceuta","Conakry","Dakar","Dar_es_Salaam","Djibouti","Douala","El_Aaiun","Freetown","Gaborone","Harare","Johannesburg","Juba","Kampala","Khartoum","Kigali","Kinshasa","Lagos","Libreville","Lome","Luanda","Lubumbashi","Lusaka","Malabo","Maputo","Maseru","Mbabane","Mogadishu","Monrovia","Nairobi","Ndjamena","Niamey","Nouakchott","Ouagadougou","Porto-Novo","Sao_Tome","Timbuktu","Tripoli","Tunis","Windhoek"],
	"America":["Adak","Anchorage","Anguilla","Antigua","Araguaina","Aruba","Asuncion","Atikokan","Atka","Bahia","Bahia_Banderas","Barbados","Belem","Belize","Blanc-Sablon","Boa_Vista","Bogota","Boise","Buenos_Aires","Cambridge_Bay","Campo_Grande","Cancun","Caracas","Catamarca","Cayenne","Cayman","Chicago","Chihuahua","Ciudad_Juarez","Coral_Harbour","Cordoba","Costa_Rica","Creston","Cuiaba","Curacao","Danmarkshavn","Dawson","Dawson_Creek","Denver","Detroit","Dominica","Edmonton","Eirunepe","El_Salvador","Ensenada","Fort_Nelson","Fort_Wayne","Fortaleza","Glace_Bay","Godthab","Goose_Bay","Grand_Turk","Grenada","Guadeloupe","Guatemala","Guayaquil","Guyana","Halifax","Havana","Hermosillo","Indianapolis","Inuvik","Iqaluit","Jamaica","Jujuy","Juneau","Knox_IN","Kralendijk","La_Paz","Lima","Los_Angeles","Louisville","Lower_Princes","Maceio","Managua","Manaus","Marigot","Martinique","Matamoros","Mazatlan","Mendoza","Menominee","Merida","Metlakatla","Mexico_City","Miquelon","Moncton","Monterrey","Montevideo","Montreal","Montserrat","Nassau","New_York","Nipigon","Nome","Noronha","Nuuk","Ojinaga","Panama","Pangnirtung","Paramaribo","Phoenix","Port-au-Prince","Port_of_Spain","Porto_Acre","Porto_Velho","Puerto_Rico","Punta_Arenas","Rainy_River","Rankin_Inlet","Recife","Regina","Resolute","Rio_Branco","Rosario","Santa_Isabel","Santarem","Santiago","Santo_Domingo","Sao_Paulo","Scoresbysund","Shiprock","Sitka","St_Barthelemy","St_Johns","St_Kitts","St_Lucia","St_Thomas","St_Vincent","Swift_Current","Tegucigalpa","Thule","Thunder_Bay","Tijuana","Toronto","Tortola","Vancouver","Virgin","Whitehorse","Winnipeg","Yakutat","Yellowknife"],
	"Antarctica":["Casey","Davis","DumontDUrville","Macquarie","Mawson","McMurdo","Palmer","Rothera","South_Pole","Syowa","Troll","Vostok"],
	"Asia":["Aden","Almaty","Amman","Anadyr","Aqtau","Aqtobe","Ashgabat","Ashkhabad","Atyrau","Baghdad","Bahrain","Baku","Bangkok","Barnaul","Beirut","Bishkek","Brunei","Calcutta","Chita","Choibalsan","Chongqing","Chungking","Colombo","Dacca","Damascus","Dhaka","Dili","Dubai","Dushanbe","Famagusta","Gaza","Harbin","Hebron","Ho_Chi_Minh","Hong_Kong","Hovd","Irkutsk","Istanbul","Jakarta","Jayapura","Jerusalem","Kabul","Kamchatka","Karachi","Kashgar","Kathmandu","Katmandu","Khandyga","Kolkata","Krasnoyarsk","Kuala_Lumpur","Kuching","Kuwait","Macao","Macau","Magadan","Makassar","Manila","Muscat","Nicosia","Novokuznetsk","Novosibirsk","Omsk","Oral","Phnom_Penh","Pontianak","Pyongyang","Qatar","Qostanay","Qyzylorda","Rangoon","Riyadh","Saigon","Sakhalin","Samarkand","Seoul","Shanghai","Singapore","Srednekolymsk","Taipei","Tashkent","Tbilisi","Tehran","Tel_Aviv","Thimbu","Thimphu","Tokyo","Tomsk","Ujung_Pandang","Ulaanbaatar","Ulan_Bator","Urumqi","Ust-Nera","Vientiane","Vladivostok","Yakutsk","Yangon","Yekaterinburg","Yerevan"],
	"Atlantic":["Azores","Bermuda","Canary","Cape_Verde","Faeroe","Faroe","Jan_Mayen","Madeira","Reykjavik","South_Georgia","St_Helena","Stanley"],
	"Australia":["ACT","Adelaide","Brisbane","Broken_Hill","Canberra","Currie","Darwin","Eucla","Hobart","LHI","Lindeman","Lord_Howe","Melbourne","NSW","North","Perth","Queensland","South","Sydney","Tasmania","Victoria","West","Yancowinna"],
	"Europe":["Amsterdam","Andorra","Astrakhan","Athens","Belfast","Belgrade","Berlin","Bratislava","Brussels","Bucharest","Budapest","Busingen","Chisinau","Copenhagen","Dublin","Gibraltar","Guernsey","Helsinki","Isle_of_Man","Istanbul","Jersey","Kaliningrad","Kiev","Kirov","Kyiv","Lisbon","Ljubljana","London","Luxembourg","Madrid","Malta","Mariehamn","Minsk","Monaco","Moscow","Nicosia","Oslo","Paris","Podgorica","Prague","Riga","Rome","Samara","San_Marino","Sarajevo","Saratov","Simferopol","Skopje","Sofia","Stockholm","Tallinn","Tirane","Tiraspol","Ulyanovsk","Uzhgorod","Vaduz","Vatican","Vienna","Vilnius","Volgograd","Warsaw","Zagreb","Zaporozhye","Zurich"],
	"Indian":["Antananarivo","Chagos","Christmas","Cocos","Comoro","Kerguelen","Mahe","Maldives","Mauritius","Mayotte","Reunion"],
	"Pacific":["Apia","Auckland","Bougainville","Chatham","Chuuk","Easter","Efate","Enderbury","Fakaofo","Fiji","Funafuti","Galapagos","Gambier","Guadalcanal","Guam","Honolulu","Johnston","Kanton","Kiritimati","Kosrae","Kwajalein","Majuro","Marquesas","Midway","Nauru","Niue","Norfolk","Noumea","Pago_Pago","Palau","Pitcairn","Pohnpei","Ponape","Port_Moresby","Rarotonga","Saipan","Samoa","Tahiti","Tarawa","Tongatapu","Truk","Wake","Wallis","Yap"]
};

function on_load(){
    const continentSelect = document.getElementById("continent");
    const citySelect = document.getElementById("city");

    // Populate the continent dropdown
    for (const continent in timezone_dict) {
        let option = document.createElement("option");
        option.value = continent;
        option.text = continent;
        continentSelect.appendChild(option);
    }

    continentSelect.addEventListener("change", function() {
        const selectedContinent = this.value;
        const cities = timezone_dict[selectedContinent] || [];

        citySelect.innerHTML = "";

        for (const city of cities) {
            let option = document.createElement("option");
            option.value = city;
            option.text = city;
            citySelect.appendChild(option);
        }
    });

    get_available_wifi(0);
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


function error(msg){
    alert(`Something went wrong:\n${msg}`);
}















// ####################################################
// ####################### WIFI ####################### 
// ####################################################


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

            watch_status()


        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });


}



function watch_status(){
    url = `/check_wifi_verification`;
    
        fetch(url)
        .then(response => {
            // Check if the response is successful (status code 200-299)
            if (!response.ok) {
                
                throw new Error('Network response was not ok');
            }
            // Parse the response body as JSON
            return response.json();
        })
        .then(response => {
            // Handle the parsed data
            console.log(response);
            let status = response["status"];
            if(status == 0){
                document.getElementById("wifiResponse").innerHTML = "Verification failed to trigger";
            }
            if(status == 1){
                document.getElementById("wifiResponse").innerHTML = "Trying to connect...";
                setTimeout(watch_status, 1000);
            }
            if(status == 2){
                document.getElementById("wifiResponse").innerHTML = "Connection successful!";
            }
            if(status == 3){
                document.getElementById("wifiResponse").innerHTML = "Could not verify credentials. Credentials may be correct.";
            }


        })
        .catch(error => {
            // Handle any errors that occurred during the fetch
            console.error('There has been a problem with your fetch operation:', error);
        });



}




let max_retries = 5;
let retry_num = 0;
let prev_response = "";
function get_available_wifi(rescan) {
    url = `/get_available_wifi`;
    if(rescan){
        url += "?rescan=1"
    }
    console.log(url);
    const ssid_select = document.getElementById("ssid");
    while (ssid_select.options.length > 0) {
        ssid_select.remove(0);
    }
    let defaultOption = document.createElement("option");
    defaultOption.value = "";
    defaultOption.disabled = true;
    defaultOption.selected = true;
    defaultOption.textContent = "Searching...";
    ssid_select.appendChild(defaultOption);


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
            while (ssid_select.options.length > 0) {
                ssid_select.remove(0);
            }

            if (response === "" || response == prev_response) {
                
                let defaultOption = document.createElement("option");
                defaultOption.value = "";
                defaultOption.disabled = true;
                defaultOption.selected = true;

                retry_num += 1;
                if (retry_num <= max_retries){
                    defaultOption.textContent = "Searching...";
                    ssid_select.appendChild(defaultOption);
                    console.log("Queuing get_available");
                    setTimeout(get_available_wifi(1), 10000); // Retry after 10 seconds
                    return;
                    
                }
                else{
                    if (response == ""){                    
                        defaultOption.textContent = "No networks found";
                        ssid_select.appendChild(defaultOption);
                        return;

                    }else{
                        console.log("Hit this else");
                    }
                }
            }

            prev_response = response;
            const ssid_list = response.split("\n");


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

document.addEventListener('DOMContentLoaded', function() {
    get_available_wifi();
});















// ####################################################
// #################### Timezone ###################### 
// ####################################################


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


document.addEventListener("DOMContentLoaded", on_load);