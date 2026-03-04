import time
import random

class SimpleSessionManager:
    def __init__(self):
        self.sessions = {} # Stores session_id: user_data

    def create_session(self, user_data):
        # In a real app, generate a secure unique ID
        session_id = str(random.randint(10000, 99999)) + "_" + str(int(time.time()))
        self.sessions[session_id] = user_data
        print(f"Session created for user: {user_data.get('username', 'N/A')} with ID: {session_id}")
        return session_id

    def get_user_data(self, session_id):
        # Simulate a delay or potential race condition here
        time.sleep(random.uniform(0.01, 0.1)) # Added to potentially expose timing issues

        print(f"Attempting to retrieve data for session ID: {session_id}")
        user_data = self.sessions.get(session_id)
        if user_data:
             print(f"Retrieved data for user: {user_data.get('username', 'N/A')}")
        else:
             print(f"No data found for session ID: {session_id}")
        return user_data

    def end_session(self, session_id):
        if session_id in self.sessions:
            del self.sessions[session_id]
            print(f"Session ended for ID: {session_id}")

# In the real app, multiple requests/threads interact with a single instance of SimpleSessionManager
# Example of problematic sequence (hard to reproduce manually):
# Thread 1: create_session(user_A_data) -> session_id_A
# Thread 2: create_session(user_B_data) -> session_id_B
# Thread 1: get_user_data(session_id_A) -> sometimes gets user_B_data here intermittently