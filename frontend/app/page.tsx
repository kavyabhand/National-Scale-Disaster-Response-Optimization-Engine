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
      <h1 className="text-4xl font-bold mb-6 text-black">
        Disaster Response Optimization Dashboard
      </h1>

      <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Total Regions</h2>
          <p className="text-3xl mt-2 text-black">{data.total_regions}</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Population Affected</h2>
          <p className="text-3xl mt-2 text-black">{data.population_affected}</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold text-gray-700">Top Priority Region</h2>
          <p className="text-3xl mt-2 text-black">{data.priority_order[0].name}</p>
        </div>
      </div>
    </main>
  );
}