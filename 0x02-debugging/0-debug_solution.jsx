import React, { useState, useEffect, useRef } from 'react';
import { createRoot } from 'react-dom/client'; // For React 18+

const App = () => {
    const [data, setData] = useState([]);
    const [isFetching, setIsFetching] = useState(false);
    const [error, setError] = useState(null);
    const [updateInterval, setUpdateInterval] = useState(1000); // Milliseconds

    // Ref to hold the interval ID
    const intervalRef = useRef(null);

    // Simulate fetching new data
    const fetchData = () => {
        console.log('Fetching data...');
        // Simulate a potential error occasionally
        if (Math.random() < 0.1) {
            setError('Failed to fetch data!');
            return;
        }

        // Simulate receiving new data
        const newDataPoint = {
            id: Date.now() + Math.random(), // Unique ID
            value: Math.random() * 100,
            timestamp: new Date().toLocaleTimeString(),
        };

        setData(prevData => [...prevData, newDataPoint]);
        setError(null);
    };

    useEffect(() => {
        if (isFetching) {
            console.log(`Starting data fetch interval (${updateInterval}ms)...`);
            intervalRef.current = setInterval(() => {
                fetchData(); // Call the fetch function
            }, updateInterval);
        } else {
            console.log('Stopping data fetch interval...');
        }

        return () => {
        };

    }, [isFetching, updateInterval]); // Dependency array

    const startFetching = () => {
        setIsFetching(true);
        setError(null); 
    };

    const stopFetching = () => {
        setIsFetching(false);
    };

    const handleIntervalChange = (e) => {
        const newInterval = Number(e.target.value);
        if (!isNaN(newInterval) && newInterval >= 100) {
            setUpdateInterval(newInterval);
        }
    };

    return (
        <div className="p-4 flex flex-col items-center bg-gray-100 min-h-screen">
            <h1 className="text-2xl font-bold mb-4">Simulated Data Fetcher</h1>

            <div className="mb-4 flex space-x-4">
                <button
                    className={`px-6 py-3 rounded font-bold transition duration-200 text-white
                                ${isFetching ? 'bg-gray-500 cursor-not-allowed' : 'bg-green-500 hover:bg-green-700'}`}
                    onClick={startFetching}
                    disabled={isFetching}
                >
                    Start Fetching
                </button>
                <button
                    className={`px-6 py-3 rounded font-bold transition duration-200 text-white
                                ${!isFetching ? 'bg-gray-500 cursor-not-allowed' : 'bg-red-500 hover:bg-red-700'}`}
                    onClick={stopFetching}
                    disabled={!isFetching}
                >
                    Stop Fetching
                </button>
                <div className="flex items-center">
                    <label htmlFor="interval" className="mr-2">Interval (ms):</label>
                    <input
                        id="interval"
                        type="number"
                        value={updateInterval}
                        onChange={handleIntervalChange}
                        className="w-24 px-2 py-1 border rounded"
                        min="100"
                        step="100"
                    />
                </div>
            </div>

            {error && (
                <p className="text-red-600 text-lg mb-4">{error}</p>
            )}

            <div className="w-full max-w-md bg-white p-4 rounded shadow-md">
                <h2 className="text-xl font-semibold mb-2">Fetched Data:</h2>
                <ul className="list-disc pl-5 max-h-60 overflow-y-auto">
                    {data.map(item => (
                        <li key={item.id} className="text-sm">{item.timestamp}: {item.value.toFixed(2)}</li>
                    ))}
                     {data.length === 0 && <p className="text-gray-500 italic">No data fetched yet.</p>}
                </ul>
            </div>
        </div>
    );
};


export default App;