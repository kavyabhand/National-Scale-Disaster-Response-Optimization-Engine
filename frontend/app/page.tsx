"use client";

import { useEffect, useState } from "react";
import {
  BarChart,
  Bar,
  XAxis,
  YAxis,
  Tooltip,
  ResponsiveContainer,
} from "recharts";

export default function Home() {
  const [data, setData] = useState<any>(null);

  useEffect(() => {
    fetch("/data/results.json")
      .then((res) => res.json())
      .then((json) => setData(json));
  }, []);

  if (!data) return <div className="p-8 text-black">Loading...</div>;

  return (
    <main className="min-h-screen bg-slate-100 text-black">
      <div className="max-w-7xl mx-auto px-8 py-10">
        <h1 className="text-5xl font-bold mb-2">
          National Disaster Response Dashboard
        </h1>
        <p className="text-gray-600 mb-10">
          Real-Time Resource Prioritization & Rescue Allocation Engine
        </p>

        <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-10">
          <StatCard title="Total Regions" value={data.total_regions} />
          <StatCard title="Population Affected" value={data.population_affected.toLocaleString()} />
          <StatCard title="Top Priority Region" value={data.priority_order[0].name} />
        </div>

        <div className="grid grid-cols-1 xl:grid-cols-2 gap-8 mb-10">
          <div className="bg-white rounded-2xl shadow p-6">
            <h2 className="text-2xl font-bold mb-4">Rescue Priority Rankings</h2>

            <div className="overflow-x-auto">
              <table className="w-full">
                <thead>
                  <tr className="border-b text-left text-gray-600">
                    <th className="py-3">Rank</th>
                    <th>Region</th>
                    <th>Population</th>
                    <th>Damage</th>
                    <th>Urgency</th>
                  </tr>
                </thead>
                <tbody>
                  {data.priority_order.map((region: any, index: number) => (
                    <tr key={index} className="border-b hover:bg-slate-50">
                      <td className="py-3 font-semibold">{index + 1}</td>
                      <td>{region.name}</td>
                      <td>{region.population.toLocaleString()}</td>
                      <td>{region.damage_level}</td>
                      <td>{region.urgency_score.toLocaleString()}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </div>

          <div className="bg-white rounded-2xl shadow p-6">
            <h2 className="text-2xl font-bold mb-4">Urgency Score Analysis</h2>

            <div className="w-full h-96">
              <ResponsiveContainer width="100%" height="100%">
                <BarChart data={data.priority_order}>
                  <XAxis dataKey="name" hide />
                  <YAxis />
                  <Tooltip />
                  <Bar dataKey="urgency_score" fill="#2563eb" radius={[6, 6, 0, 0]} />
                </BarChart>
              </ResponsiveContainer>
            </div>
          </div>
        </div>
      </div>
    </main>
  );
}

function StatCard({ title, value }: { title: string; value: string | number }) {
  return (
    <div className="bg-white rounded-2xl shadow p-6">
      <h2 className="text-lg font-semibold text-gray-600">{title}</h2>
      <p className="text-3xl font-bold mt-3">{value}</p>
    </div>
  );
}