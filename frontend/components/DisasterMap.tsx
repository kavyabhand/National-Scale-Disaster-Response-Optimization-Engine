"use client";

import { MapContainer, TileLayer, CircleMarker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";

export default function DisasterMap({ data }: { data: any[] }) {
    const mapProps: any = {
        center: [20, 0],
        zoom: 2,
        className: "h-[500px] w-full rounded-2xl",
    };

    return (
        <MapContainer {...mapProps}>
            <TileLayer url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png" />

            {data.map((region, index) => (
                <CircleMarker
                    key={index}
                    center={[region.latitude, region.longitude] as any}
                    {...({ radius: Math.max(region.damage_level * 2, 6) } as any)}
                    pathOptions={{ color: "red" }}
                >
                    <Popup>
                        <div>
                            <h3 className="font-bold">{region.name}</h3>
                            <p>Urgency: {region.urgency_score}</p>
                            <p>Population: {region.population}</p>
                        </div>
                    </Popup>
                </CircleMarker>
            ))}
        </MapContainer>
    );
}