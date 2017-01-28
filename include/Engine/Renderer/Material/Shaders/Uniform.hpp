#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Matrix4.hpp"
#include "Engine/Renderer/Material/Shaders/Sampler2D.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include <vector>
#include <string>

enum eUniformType {
	UNIFORM_FLOAT = 0,
	UNIFORM_DOUBLE,
	UNIFORM_VECTOR3,
	UNIFORM_VECTOR2,
	UNIFORM_VECTOR4,
	UNIFORM_MAT4,
	UNIFORM_INT,
	UNIFORM_SHORT,
	UNIFORM_SAMPLER2D,
	UNIFORM_RGBA
};

//---------------------------------------------------------------------------------------------------------------------------
//BASE CLASS UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform {
public:
	//STRUCTORS
	Uniform(const std::string& name, eUniformType type)
		: m_name(name)
		, m_type(type)
	{ }

	//GETTERS SETTERS
	virtual eUniformType GetType() = 0;
	virtual std::string GetName() = 0;

protected:
	std::string m_name;
	eUniformType m_type;
};

//---------------------------------------------------------------------------------------------------------------------------
//FLOAT UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_FLOAT : public Uniform {
public:
	Uniform_FLOAT(const std::string name, const std::vector<float> data) : Uniform(name, UNIFORM_FLOAT) {
		m_data = data;
	}
	Uniform_FLOAT(const std::string name, float data) : Uniform(name, UNIFORM_FLOAT) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<float> GetData() { return m_data; }
	void SetData(const std::vector<float>& data) { m_data = data; }
	void SetData(float data) { 
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<float> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//DOUBLE UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_DOUBLE : public Uniform {
public:
	Uniform_DOUBLE(const std::string name, const std::vector<double> data) : Uniform(name, UNIFORM_DOUBLE) {
		m_data = data;
	}
	Uniform_DOUBLE(const std::string name, double data) : Uniform(name, UNIFORM_DOUBLE) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<double> GetData() { return m_data; }
	void SetData(const std::vector<double>& data) { m_data = data; }
	void SetData(double data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<double> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//VECTOR2 UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_VECTOR2 : public Uniform {
public:
	Uniform_VECTOR2(const std::string name, const std::vector<Vector2> data) : Uniform(name, UNIFORM_VECTOR2) {
		m_data = data;
	}
	Uniform_VECTOR2(const std::string name, Vector2 data) : Uniform(name, UNIFORM_VECTOR2) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<Vector2> GetData() { return m_data; }
	void SetData(const std::vector<Vector2>& data) { m_data = data; }
	void SetData(Vector2 data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<Vector2> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//VECTOR3 UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_VECTOR3 : public Uniform {
public:
	Uniform_VECTOR3(const std::string name, const std::vector<Vector3> data) : Uniform(name, UNIFORM_VECTOR3) {
		m_data = data;
	}
	Uniform_VECTOR3(const std::string name, Vector3 data) : Uniform(name, UNIFORM_VECTOR3) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<Vector3> GetData() { return m_data; }
	void SetData(const std::vector<Vector3>& data) { m_data = data; }
	void SetData(Vector3 data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<Vector3> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//VECTOR4 UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_VECTOR4 : public Uniform {
public:
	Uniform_VECTOR4(const std::string name, const std::vector<Vector4> data) : Uniform(name, UNIFORM_VECTOR4) {
		m_data = data;
	}
	Uniform_VECTOR4(const std::string name, Vector4 data) : Uniform(name, UNIFORM_VECTOR4) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<Vector4> GetData() { return m_data; }
	void SetData(const std::vector<Vector4>& data) { m_data = data; }
	void SetData(Vector4 data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<Vector4> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//MAT4 UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_MAT4 : public Uniform {
public:
	Uniform_MAT4(const std::string name, const std::vector<Matrix4> data) : Uniform(name, UNIFORM_MAT4) {
		m_data = data;
	}
	Uniform_MAT4(const std::string name, Matrix4 data) : Uniform(name, UNIFORM_MAT4) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<Matrix4> GetData() { return m_data; }
	void SetData(const std::vector<Matrix4>& data) { m_data = data; }
	void SetData(Matrix4 data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<Matrix4> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//INT UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_INT : public Uniform {
public:
	Uniform_INT(const std::string name, const std::vector<int> data) : Uniform(name, UNIFORM_INT) {
		m_data = data;
	}
	Uniform_INT(const std::string name, int data) : Uniform(name, UNIFORM_INT) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<int> GetData() { return m_data; }
	void SetData(const std::vector<int>& data) { m_data = data; }
	void SetData(int data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<int> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//SHORT UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_SHORT : public Uniform {
public:
	Uniform_SHORT(const std::string name, const std::vector<short> data) : Uniform(name, UNIFORM_SHORT) {
		m_data = data;
	}
	Uniform_SHORT(const std::string name, short data) : Uniform(name, UNIFORM_SHORT) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<short> GetData() { return m_data; }
	void SetData(const std::vector<short>& data) { m_data = data; }
	void SetData(short data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<short> m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//SAMPLER2D UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_SAMPLER2D : public Uniform {
public:
// 	Uniform_FLOAT(const std::string name, UniformType type, const std::vector<Sampler2D> data) : Uniform(name, type) {
// 		m_data = data;
// 	}
	Uniform_SAMPLER2D(Sampler2D data) : Uniform("SAMPLER2D", UNIFORM_SAMPLER2D) {
		m_data = data;
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	Sampler2D GetData() { return m_data; }
	void SetData(Sampler2D data) {
		m_data = data;
	}

private:
	Sampler2D m_data;
};

//---------------------------------------------------------------------------------------------------------------------------
//RGBA UNIFORM
//---------------------------------------------------------------------------------------------------------------------------
class Uniform_RGBA : public Uniform {
public:
	Uniform_RGBA(const std::string name, const std::vector<RGBA> data) : Uniform(name, UNIFORM_RGBA) {
		m_data = data;
	}
	Uniform_RGBA(const std::string name, RGBA data) : Uniform(name, UNIFORM_RGBA) {
		m_data.push_back(data);
	}

	eUniformType GetType() { return m_type; }
	std::string GetName() { return m_name; }
	std::vector<RGBA> GetData() { return m_data; }
	void SetData(const std::vector<RGBA>& data) { m_data = data; }
	void SetData(RGBA data) {
		m_data.clear();
		m_data.push_back(data);
	}

private:
	std::vector<RGBA> m_data;
};