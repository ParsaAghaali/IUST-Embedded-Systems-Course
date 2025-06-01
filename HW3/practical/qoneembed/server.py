from flask import Flask

app = Flask(__name__)

@app.route('/heartbeat', methods=['GET'])
def heartbeat():
    return "Heartbeat received!", 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)