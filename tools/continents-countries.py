import zoneinfo

# Define the continents we're interested in
continents = ['Africa', 'America', 'Antarctica', 'Asia', 'Atlantic', 'Australia', 'Europe', 'Indian', 'Pacific']

# Initialize an empty dictionary to store cities per continent
timezones_by_continent = {continent: [] for continent in continents}

# Iterate over all time zones available in the zoneinfo module
for timezone in zoneinfo.available_timezones():
    # Split the timezone into continent and city
    parts = timezone.split('/')
    if len(parts) == 2:  # We are only interested in continent/city format
        continent, city = parts
        # If the continent is in our list, add the city to that continent's list
        if continent in continents:
            timezones_by_continent[continent].append(city)



output_dict = dict()

for continent, cities in timezones_by_continent.items():
    cities = sorted(cities)
    cities = ['"' + i + '"' for i in cities]    
    cities_str = "[" + ",".join(cities) + "]"
    output_dict[continent] = cities_str


timezone_str = "const timezone_dict = {\n"
for key, val in output_dict.items():
    timezone_str += "\t"
    timezone_str += f'"{key}":{val},\n'


timezone_str = timezone_str[:-2]
timezone_str += "\n};"

w = open("out.txt", "w")
w.write(timezone_str)
w.close()