import requests
import json
import random

url = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_day.geojson"

response = requests.get(url)
data = response.json()

events = []

for quake in data["features"][:10]:
    props = quake["properties"]

    magnitude = props["mag"] or 0

    population = random.randint(100000, 2000000)

    damage_level = min(max(int(magnitude * 2), 1), 10)

    coordinates = quake["geometry"]["coordinates"]

    events.append({
        "name": props["place"],
        "population": population,
        "damage_level": damage_level,
        "latitude": coordinates[1],
        "longitude": coordinates[0]
    })

with open("data/live_disasters.json", "w") as f:
    json.dump(events, f, indent=4)

print("Live disaster data fetched.")