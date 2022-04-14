#pragma once

#include <string>


class Vector2;
class Vector3;
class Vector4;
class Quaternion;
class Color;
class Matrix;

namespace Xml
{
	class XMLDocument;
	class XMLDeclaration;
	class XMLElement;
}

namespace XmlHelper
{
	class WriteNode;
	class ReadNode;
	class Helper;

	static const char* BoolTypeStr = "Bool";
	static const char* IntTypeStr = "Int";
	static const char* FloatTypeStr = "Float";
	static const char* DoubleTypeStr = "Double";
	static const char* UnsignedTypeStr = "Unsigned";
	static const char* Int64TypeStr = "Int64";
	static const char* StringTypeStr = "String";
	static const char* Vector2TypeStr = "Vector2";
	static const char* Vector3TypeStr = "Vector3";
	static const char* Vector4TypeStr = "Vector4";
	static const char* QuaternionTypeStr = "Quaternion";
	static const char* ColorTypeStr = "Color";
	static const char* MatrixTypeStr = "Matrix";

	enum class XmlMode
	{
		NONE = 0, WRITE = 1, READ = 2
	};

	class Helper
	{
	public:
		Helper();
		~Helper();

		WriteNode writeStart(std::string rootName);
		ReadNode readStart(std::string fileName);
		ReadNode readStart(std::wstring fileName);

		void saveFile(std::string fileName);
		void saveFile(std::wstring fileName);

		std::string getRootName() { return rootName; }
		std::string getFileName() { return fileName; }

		XmlMode currentMode() { return mode; }

		void Release();

	private:
		XmlMode mode = XmlMode::NONE;

		std::string rootName;
		std::string fileName;

		Xml::XMLDocument* document;
		Xml::XMLDeclaration *decl;
	};

	class WriteNode
	{
	public:
		friend class Helper;

		WriteNode() : parentNode(NULL), element(NULL), document(NULL), name("") {}

		void operator= (const WriteNode& val)
		{
			name = val.name;
			element = val.element;
			document = val.document;
			parentNode = val.parentNode;
		}

		void operator >> (const bool& data) { addData(data); }
		void operator >> (const int& data) { addData(data); }
		void operator >> (const float& data) { addData(data); }
		void operator >> (const double& data) { addData(data); }
		void operator >> (const unsigned int& data) { addData(data); }
		void operator >> (const int64_t& data) { addData(data); }
		void operator >> (const std::string& data) { addData(data); }
		void operator >> (const char* data) { addData(data); }
		void operator >> (const std::wstring& data) { addData(data); }
		void operator >> (const Vector2& data) { addData(data); }
		void operator >> (const Vector3& data) { addData(data); }
		void operator >> (const Vector4& data) { addData(data); }
		void operator >> (const Quaternion& data) { addData(data); }
		void operator >> (const Color& data) { addData(data); }
		void operator >> (const Matrix& data) { addData(data); }

		WriteNode addChild(std::string childName);
		WriteNode addChild(std::string childName, const bool& data);
		WriteNode addChild(std::string childName, const int& data);
		WriteNode addChild(std::string childName, const float& data);
		WriteNode addChild(std::string childName, const double& data);
		WriteNode addChild(std::string childName, const unsigned int& data);
		WriteNode addChild(std::string childName, const int64_t& data);
		WriteNode addChild(std::string childName, const std::string& data);
		WriteNode addChild(std::string childName, const char* data);
		WriteNode addChild(std::string childName, const std::wstring& data);

		WriteNode addChild(std::string childName, const Vector2& data);
		WriteNode addChild(std::string childName, const Vector3& data);
		WriteNode addChild(std::string childName, const Vector4& data);
		WriteNode addChild(std::string childName, const Quaternion& data);
		WriteNode addChild(std::string childName, const Color& data);
		WriteNode addChild(std::string childName, const Matrix& data);

		void addData(const bool& data);
		void addData(const int& data);
		void addData(const float& data);
		void addData(const double& data);
		void addData(const unsigned int& data);
		void addData(const int64_t& data);
		void addData(const std::string& data);
		void addData(const char* data);
		void addData(const std::wstring& data);

		void addData(const Vector2& data);
		void addData(const Vector3& data);
		void addData(const Vector4& data);
		void addData(const Quaternion& data);
		void addData(const Color& data);
		void addData(const Matrix& data);

		void SetType(const char* typeName);

		WriteNode getParentNode() { return *parentNode; }
		std::string getName() { return name; }

		Xml::XMLElement* GetElement() { return element; }

	private:
		std::string name;
		Xml::XMLElement* element;
		Xml::XMLDocument* document;

		WriteNode* parentNode;
	};

	class ReadNode
	{
	public:
		friend class Helper;

		ReadNode() : element(NULL), document(NULL), name(""), bEmpty(false), currentChildNode(NULL) {}
		~ReadNode() { delete currentChildNode; currentChildNode = 0; }

		void operator= (const ReadNode& val)
		{
			bEmpty = val.bEmpty;
			name = val.name;
			element = val.element;
			document = val.document;
		}

		bool getBool();
		int getInt();
		float getFloat();
		double getDouble();
		unsigned int getUnsigned();
		int64_t getInt64();
		std::string getString();
		std::wstring getWString();
		Vector2 getVector2(ReadNode* outNextChild = NULL);
		Vector3 getVector3(ReadNode* outNextChild = NULL);
		Vector4 getVector4(ReadNode* outNextChild = NULL);
		Quaternion getQuaternion(ReadNode* outNextChild = NULL);
		Color getColor(ReadNode* outNextChild = NULL);
		Matrix getMatrix(ReadNode* outNextChild = NULL);


		Xml::XMLElement* GetElement() { return element; }

		ReadNode next();
		ReadNode firstChild();

		void iteratorStart();
		ReadNode iteratorChild();
		void iteratorEnd();

		bool isEmpty() { return bEmpty; }
		std::string getType();
		std::string getName() { return name; }

	private:
		static ReadNode Create(Xml::XMLElement* e, Xml::XMLDocument* d);

	private:
		bool bEmpty;

		std::string name;
		Xml::XMLElement* element;
		Xml::XMLDocument* document;

		ReadNode* currentChildNode;
	};
}