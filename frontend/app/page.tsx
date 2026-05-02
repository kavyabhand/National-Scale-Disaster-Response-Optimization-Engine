export default function Home() {
  return (
    <main className="min-h-screen bg-gray-100 p-8">
      <h1 className="text-4xl font-bold mb-6">
        Disaster Response Optimization Dashboard
      </h1>

      <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold">Total Regions</h2>
          <p className="text-3xl mt-2">5</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold">Population Affected</h2>
          <p className="text-3xl mt-2">1,600,000</p>
        </div>

        <div className="bg-white p-6 rounded-xl shadow">
          <h2 className="text-xl font-semibold">Top Priority Region</h2>
          <p className="text-3xl mt-2">Mumbai</p>
        </div>
      </div>
    </main>
  );
}