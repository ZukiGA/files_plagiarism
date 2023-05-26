from flask import Flask, jsonify, request, abort
from flask_sqlalchemy import SQLAlchemy
from flask_httpauth import HTTPBasicAuth

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///cafe_users.db'
db = SQLAlchemy(app)
auth = HTTPBasicAuth()

# Autenticación básica
@auth.verify_password
def verify_password(username, password):
    # Verifica las credenciales de autenticación
    if username == 'admin' and password == 'password':
        return True
    return False

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    email = db.Column(db.String(100), unique=True, nullable=False)

    def __init__(self, name, email):
        self.name = name
        self.email = email

@app.route('/users', methods=['GET'])
@auth.login_required
def get_users():
    users = User.query.all()
    user_list = []
    for user in users:
        user_data = {'id': user.id, 'name': user.name, 'email': user.email}
        user_list.append(user_data)
    return jsonify({'users': user_list})

@app.route('/users', methods=['POST'])
@auth.login_required
def create_user():
    name = request.json['name']
    email = request.json['email']
    new_user = User(name, email)
    db.session.add(new_user)
    db.session.commit()
    return jsonify({'message': 'User created successfully'})

@app.route('/users/<int:user_id>', methods=['PUT'])
@auth.login_required
def update_user(user_id):
    user = User.query.get(user_id)
    if not user:
        return jsonify({'message': 'User not found'})
    user.name = request.json['name']
    user.email = request.json['email']
    db.session.commit()
    return jsonify({'message': 'User updated successfully'})

@app.route('/users/<int:user_id>', methods=['DELETE'])
@auth.login_required
def delete_user(user_id):
    user = User.query.get(user_id)
    if not user:
        return jsonify({'message': 'User not found'})
    db.session.delete(user)
    db.session.commit()
    return jsonify({'message': 'User deleted successfully'})

if __name__ == '__main__':
    app.run(debug=True)
