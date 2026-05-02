"use client";

import { useEffect, useMemo, useState } from "react";
import dynamic from "next/dynamic";
import {
  BarChart,
  Bar,
  XAxis,
  YAxis,
  Tooltip,
  ResponsiveContainer,
} from "recharts";

const DisasterMap = dynamic(() => import("../components/DisasterMap"), {
  ssr: false,
});

type Region = {
  name: string;
  population: number;
  damage_level: number;
  urgency_score: number;
  latitude: number;
  longitude: number;
};

export default function Home() {
  const [data, setData] = useState<any>(null);
  const [search, setSearch] = useState("");
  const [minUrgency, setMinUrgency] = useState<number>(0);

  useEffect(() => {
    fetch("/data/results.json")
      .then((res) => res.json())
      .then((json) => setData(json))
      .catch((err) => console.error("Failed to load data:", err));
  }, []);

  // Safe fallback
  const priorityOrder: Region[] = data?.priority_order ?? [];

  // Filter + search + urgency filter
  const filteredRegions = useMemo(() => {
    return priorityOrder.filter((region: Region) => {
      return (
        region.name.toLowerCase().includes(search.toLowerCase()) &&
        region.urgency_score >= minUrgency
      );
    });
  }, [priorityOrder, search, minUrgency]);

  // Safe sorting (highest urgency first)
  const sortedRegions = useMemo(() => {
    return [...filteredRegions].sort(
      (a, b) => b.urgency_score - a.urgency_score
    );
  }, [filteredRegions]);

  if (!data) {
    return <div className="p-8 text-black">Loading disaster data...</div>;
  }

  return (
    <main className="min-h-screen bg-slate-100 text-black">
      <div className="max-w-7xl mx-auto px-8 py-10">
        <h1 className="text-5xl font-bold mb-2">
          National Disaster Response Dashboard
        </h1>

        <p className="text-gray-600 mb-10">
          Real-Time Resource Prioritization & Rescue Allocation Engine
        </p>

        {/* Filters */}
        <div className="bg-white rounded-2xl shadow p-6 mb-8 flex flex-col md:flex-row gap-4">
          <input
            type="text"
            placeholder="Search region..."
            value={search}
            onChange={(e) => setSearch(e.target.value)}
            className="border rounded-xl px-4 py-3 flex-1"
          />

          <input
            type="number"
            placeholder="Minimum urgency"
            value={minUrgency}
            onChange={(e) => setMinUrgency(Number(e.target.value))}
            className="border rounded-xl px-4 py-3 w-full md:w-64"
          />
        </div>

        {/* Stats */}
        <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-10">
          <StatCard title="Total Regions" value={sortedRegions.length} />

          <StatCard
            title="Population Affected"
            value={
              data.population_affected
                ? data.population_affected.toLocaleString()
                : "0"
            }
          />

          <StatCard
            title="Top Priority Region"
            value={sortedRegions[0]?.name || "N/A"}
          />
        </div>

        {/* Table + Chart */}
        <div className="grid grid-cols-1 xl:grid-cols-2 gap-8 mb-10">
          {/* Table */}
          <div className="bg-white rounded-2xl shadow p-6">
            <h2 className="text-2xl font-bold mb-4">
              Rescue Priority Rankings
            </h2>

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
                  {sortedRegions.map((region: Region, index: number) => (
                    <tr key={index} className="border-b hover:bg-slate-50">
                      <td className="py-3 font-semibold">{index + 1}</td>
                      <td>{region.name}</td>
                      <td>{region.population.toLocaleString()}</td>
                      <td>{region.damage_level}</td>
                      <td>{region.urgency_score}</td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </div>

          {/* Chart */}
          <div className="bg-white rounded-2xl shadow p-6">
            <h2 className="text-2xl font-bold mb-4">
              Urgency Score Analysis
            </h2>

            <div className="w-full h-96">
              <ResponsiveContainer width="100%" height="100%">
                <BarChart data={sortedRegions}>
                  <XAxis dataKey="name" hide />
                  <YAxis />
                  <Tooltip />
                  <Bar dataKey="urgency_score" />
                </BarChart>
              </ResponsiveContainer>
            </div>
          </div>
        </div>

        {/* Map */}
        <div className="bg-white rounded-2xl shadow p-6 mt-10">
          <h2 className="text-2xl font-bold mb-4">Live Disaster Map</h2>
          <DisasterMap data={sortedRegions} />
        </div>
      </div>
    </main>
  );
}

/* ---------------- STAT CARD ---------------- */

function StatCard({
  title,
  value,
}: {
  title: string;
  value: string | number;
}) {
  return (
    <div className="bg-white rounded-2xl shadow p-6">
      <h2 className="text-lg font-semibold text-gray-600">{title}</h2>
      <p className="text-3xl font-bold mt-3">{value}</p>
    </div>
  );
}