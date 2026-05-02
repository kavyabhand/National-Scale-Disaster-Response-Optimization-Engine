import requests
import json

url = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_day.geojson"

response = requests.get(url)
data = response.json()

events = []

for quake in data["features"][:10]:
    props = quake["properties"]

    events.append({
        "name": props["place"],
        "magnitude": props["mag"] or 0,
        "population": 500000,
        "damage_level": min(int((props["mag"] or 0) * 2), 10)
    })

with open("data/live_disasters.json", "w") as f:
    json.dump(events, f, indent=4)

print("Live disaster data fetched.")