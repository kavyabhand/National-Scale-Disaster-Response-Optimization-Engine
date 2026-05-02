source venv/bin/activate
python fetch_live_data.py
./disaster
cp data/results.json ../frontend/public/data/results.json
echo "Dashboard data refreshed."