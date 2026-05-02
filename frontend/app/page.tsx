"use client";

import { useEffect, useState } from "react";

export default function Home() {
  const [data, setData] = useState<any>(null);

  useEffect(() => {
    fetch("/data/results.json")
      .then((res) => res.json())
      .then((json) => setData(json));
  }, []);

  if (!data) return <div className="p-8 text-black">Loading...</div>;

  return (
    <main className="min-h-screen bg-gray-100 p-8 text-black">
      <h1 className="text-4xl font-bold mb-6">
        Disaster Response Optimization Dashboard
      </h1>

      <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-10">
        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Total Regions</h2>
          <p className="text-3xl mt-2">{data.total_regions}</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Population Affected</h2>
          <p className="text-3xl mt-2">{data.population_affected}</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Top Priority Region</h2>
          <p className="text-3xl mt-2">{data.priority_order[0].name}</p>
        </div>
      </div>

      <div className="bg-white rounded-xl shadow p-6">
        <h2 className="text-2xl font-bold mb-4">Rescue Priority Rankings</h2>

        <table className="w-full border-collapse">
          <thead>
            <tr className="border-b text-left">
              <th className="py-3">Rank</th>
              <th>Region</th>
              <th>Population</th>
              <th>Damage Level</th>
              <th>Urgency Score</th>
            </tr>
          </thead>

          <tbody>
            {data.priority_order.map((region: any, index: number) => (
              <tr key={index} className="border-b hover:bg-gray-50">
                <td className="py-3">{index + 1}</td>
                <td>{region.name}</td>
                <td>{region.population}</td>
                <td>{region.damage_level}</td>
                <td>{region.urgency_score}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </main>
  );
}