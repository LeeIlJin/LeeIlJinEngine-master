//
#include <Windows.h>
#include <assert.h>

#include "XmlHelper.h"
#include "Xml.h"

#include "../Math/MyMath.h"

#include "String.h"

using namespace std;

namespace XmlHelper
{

	Helper::Helper()
	{
		mode = XmlMode::NONE;
		rootName = "";
		fileName = "";

		document = NULL;
		decl = NULL;
	}

	Helper::~Helper()
	{
		if (mode != XmlMode::NONE)
			this->Release();
	}

	WriteNode Helper::writeStart(string rootName)
	{
		assert(mode == XmlMode::NONE && "XML UTIL Write Start Error");

		document = new Xml::XMLDocument();
		decl = document->NewDeclaration();
		document->LinkEndChild(decl);

		this->rootName = rootName;
		Xml::XMLElement* root = document->NewElement(rootName.c_str());
		root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		root->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
		document->LinkEndChild(root);

		WriteNode rootNode;
		rootNode.document = document;
		rootNode.element = root;
		rootNode.name = rootName;

		mode = XmlMode::WRITE;

		return rootNode;
	}

	ReadNode Helper::readStart(string fileName)
	{
		assert(mode == XmlMode::NONE && "XML UTIL Read Start Error");

		this->fileName = fileName;
		document = new Xml::XMLDocument();

		Xml::XMLError error = document->LoadFile(fileName.c_str());
		assert(error == Xml::XML_SUCCESS);

		Xml::XMLElement* root = document->FirstChildElement();

		ReadNode rootNode;
		rootNode.document = document;
		rootNode.element = root;
		rootNode.name = root->Name();
		this->rootName = rootNode.name;

		mode = XmlMode::READ;

		return rootNode;
	}

	ReadNode Helper::readStart(wstring fileName)
	{
		return readStart(String::ToString(fileName));
	}

	void Helper::saveFile(string fileName)
	{
		assert(mode == XmlMode::WRITE && "XML UTIL Save File Error");

		document->SaveFile(fileName.c_str());
	}

	void Helper::saveFile(wstring fileName)
	{
		saveFile(String::ToString(fileName));
	}

	void Helper::Release()
	{
		assert(mode != XmlMode::NONE && "XML UTIL Release Error");

		if (document != 0)
		{
			delete document;
			document = 0;
		}

		mode = XmlMode::NONE;
		rootName = "";
		fileName = "";

		decl = NULL;
	}



	///////////////////////////////////////////////////////////////////////////
	//		Write Node

	void WriteNode::addData(const bool& data)
	{
		SetType(BoolTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const int& data)
	{
		SetType(IntTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const float& data)
	{
		SetType(FloatTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const double& data)
	{
		SetType(DoubleTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const unsigned int& data)
	{
		SetType(UnsignedTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const int64_t& data)
	{
		SetType(Int64TypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const string& data)
	{
		SetType(StringTypeStr);
		element->SetText(data.c_str());
	}
	void WriteNode::addData(const char * data)
	{
		SetType(StringTypeStr);
		element->SetText(data);
	}
	void WriteNode::addData(const wstring& data)
	{
		SetType(StringTypeStr);
		element->SetText(String::ToString(data).c_str());
	}
	void WriteNode::addData(const Vector2& data)
	{
		element->DeleteChildren();

		SetType(Vector2TypeStr);

		Xml::XMLElement* node = document->NewElement("X");
		node->SetText(data.x);
		element->LinkEndChild(node);

		node = document->NewElement("Y");
		node->SetText(data.y);
		element->LinkEndChild(node);
	}
	void WriteNode::addData(const Vector3& data)
	{
		element->DeleteChildren();

		SetType(Vector3TypeStr);

		Xml::XMLElement* node = document->NewElement("X");
		node->SetText(data.x);
		element->LinkEndChild(node);

		node = document->NewElement("Y");
		node->SetText(data.y);
		element->LinkEndChild(node);

		node = document->NewElement("Z");
		node->SetText(data.z);
		element->LinkEndChild(node);
	}
	void WriteNode::addData(const Vector4& data)
	{
		element->DeleteChildren();

		SetType(Vector4TypeStr);

		Xml::XMLElement* node = document->NewElement("X");
		node->SetText(data.x);
		element->LinkEndChild(node);

		node = document->NewElement("Y");
		node->SetText(data.y);
		element->LinkEndChild(node);

		node = document->NewElement("Z");
		node->SetText(data.z);
		element->LinkEndChild(node);

		node = document->NewElement("W");
		node->SetText(data.w);
		element->LinkEndChild(node);
	}
	void WriteNode::addData(const Quaternion& data)
	{
		element->DeleteChildren();

		SetType(QuaternionTypeStr);

		Xml::XMLElement* node = document->NewElement("X");
		node->SetText(data.x);
		element->LinkEndChild(node);

		node = document->NewElement("Y");
		node->SetText(data.y);
		element->LinkEndChild(node);

		node = document->NewElement("Z");
		node->SetText(data.z);
		element->LinkEndChild(node);

		node = document->NewElement("W");
		node->SetText(data.w);
		element->LinkEndChild(node);
	}
	void WriteNode::addData(const Color& data)
	{
		element->DeleteChildren();

		SetType(ColorTypeStr);

		Xml::XMLElement* node = document->NewElement("R");
		node->SetText(data.r);
		element->LinkEndChild(node);

		node = document->NewElement("G");
		node->SetText(data.g);
		element->LinkEndChild(node);

		node = document->NewElement("B");
		node->SetText(data.b);
		element->LinkEndChild(node);

		node = document->NewElement("A");
		node->SetText(data.a);
		element->LinkEndChild(node);
	}
	void WriteNode::addData(const Matrix& data)
	{
		element->DeleteChildren();

		SetType(MatrixTypeStr);

		Xml::XMLElement* node = document->NewElement("M_11");
		node->SetText(data.m_11);
		element->LinkEndChild(node);

		node = document->NewElement("M_12");
		node->SetText(data.m_12);
		element->LinkEndChild(node);

		node = document->NewElement("M_13");
		node->SetText(data.m_13);
		element->LinkEndChild(node);

		node = document->NewElement("M_14");
		node->SetText(data.m_14);
		element->LinkEndChild(node);

		//

		node = document->NewElement("M_21");
		node->SetText(data.m_21);
		element->LinkEndChild(node);

		node = document->NewElement("M_22");
		node->SetText(data.m_22);
		element->LinkEndChild(node);

		node = document->NewElement("M_23");
		node->SetText(data.m_23);
		element->LinkEndChild(node);

		node = document->NewElement("M_24");
		node->SetText(data.m_24);
		element->LinkEndChild(node);

		//

		node = document->NewElement("M_31");
		node->SetText(data.m_31);
		element->LinkEndChild(node);

		node = document->NewElement("M_32");
		node->SetText(data.m_32);
		element->LinkEndChild(node);

		node = document->NewElement("M_33");
		node->SetText(data.m_33);
		element->LinkEndChild(node);

		node = document->NewElement("M_34");
		node->SetText(data.m_34);
		element->LinkEndChild(node);

		//

		node = document->NewElement("M_41");
		node->SetText(data.m_41);
		element->LinkEndChild(node);

		node = document->NewElement("M_42");
		node->SetText(data.m_42);
		element->LinkEndChild(node);

		node = document->NewElement("M_43");
		node->SetText(data.m_43);
		element->LinkEndChild(node);

		node = document->NewElement("M_44");
		node->SetText(data.m_44);
		element->LinkEndChild(node);
	}

	void WriteNode::SetType(const char * typeName)
	{
		element->SetAttribute("Type", typeName);
	}

	WriteNode WriteNode::addChild(string childName)
	{
		WriteNode node;
		node.parentNode = this;
		node.document = document;
		node.name = childName;
		node.element = document->NewElement(childName.c_str());
		element->LinkEndChild(node.element);

		return node;
	}
	WriteNode WriteNode::addChild(string childName, const bool & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const int & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const float & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const double & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const unsigned int & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const int64_t & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const string & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const char * data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const wstring & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Vector2 & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Vector3 & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Vector4 & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Quaternion & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Color & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}
	WriteNode WriteNode::addChild(string childName, const Matrix & data)
	{
		WriteNode node = addChild(childName);
		node.addData(data);
		return node;
	}

	///////////////////////////////////////////////////////////////////////////
	//		Read Node

	bool ReadNode::getBool()
	{
		return element->BoolText();
	}

	int ReadNode::getInt()
	{
		return element->IntText();
	}

	float ReadNode::getFloat()
	{
		return element->FloatText();
	}

	double ReadNode::getDouble()
	{
		return element->DoubleText();
	}

	unsigned int ReadNode::getUnsigned()
	{
		return element->UnsignedText();
	}

	int64_t ReadNode::getInt64()
	{
		return element->Int64Text();
	}

	string ReadNode::getString()
	{
		return element->GetText();
	}

	wstring ReadNode::getWString()
	{
		return String::ToWString(element->GetText());
	}

	Vector2 ReadNode::getVector2(ReadNode* outNextChild)
	{
		Vector2 val;

		Xml::XMLElement* xy = element->FirstChildElement();
		val.x = xy->FloatText();

		xy = xy->NextSiblingElement();
		val.y = xy->FloatText();

		if (outNextChild != NULL)
		{
			xy = xy->NextSiblingElement();
			*outNextChild = Create(xy, document);
		}

		return val;
	}

	Vector3 ReadNode::getVector3(ReadNode* outNextChild)
	{
		Vector3 val;

		Xml::XMLElement* xyz = element->FirstChildElement();
		val.x = xyz->FloatText();

		xyz = xyz->NextSiblingElement();
		val.y = xyz->FloatText();

		xyz = xyz->NextSiblingElement();
		val.z = xyz->FloatText();

		if (outNextChild != NULL)
		{
			xyz = xyz->NextSiblingElement();
			*outNextChild = Create(xyz, document);
		}

		return val;
	}

	Vector4 ReadNode::getVector4(ReadNode* outNextChild)
	{
		Vector4 val;

		Xml::XMLElement* xyzw = element->FirstChildElement();
		val.x = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.y = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.z = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.w = xyzw->FloatText();

		if (outNextChild != NULL)
		{
			xyzw = xyzw->NextSiblingElement();
			*outNextChild = Create(xyzw, document);
		}

		return val;
	}

	Quaternion ReadNode::getQuaternion(ReadNode* outNextChild)
	{
		Quaternion val;

		Xml::XMLElement* xyzw = element->FirstChildElement();
		val.x = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.y = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.z = xyzw->FloatText();

		xyzw = xyzw->NextSiblingElement();
		val.w = xyzw->FloatText();

		if (outNextChild != NULL)
		{
			xyzw = xyzw->NextSiblingElement();
			*outNextChild = Create(xyzw, document);
		}

		return val;
	}

	Color ReadNode::getColor(ReadNode* outNextChild)
	{
		Color val;

		Xml::XMLElement* rgba = element->FirstChildElement();
		val.r = rgba->FloatText();

		rgba = rgba->NextSiblingElement();
		val.g = rgba->FloatText();

		rgba = rgba->NextSiblingElement();
		val.b = rgba->FloatText();

		rgba = rgba->NextSiblingElement();
		val.a = rgba->FloatText();

		if (outNextChild != NULL)
		{
			rgba = rgba->NextSiblingElement();
			*outNextChild = Create(rgba, document);
		}

		return val;
	}

	Matrix ReadNode::getMatrix(ReadNode* outNextChild)
	{
		Matrix val;

		Xml::XMLElement* mat = element->FirstChildElement();
		val.m_11 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_12 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_13 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_14 = mat->FloatText();

		//

		mat = mat->NextSiblingElement();
		val.m_21 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_22 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_23 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_24 = mat->FloatText();

		//

		mat = mat->NextSiblingElement();
		val.m_31 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_32 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_33 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_34 = mat->FloatText();

		//

		mat = mat->NextSiblingElement();
		val.m_41 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_42 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_43 = mat->FloatText();
		mat = mat->NextSiblingElement();
		val.m_44 = mat->FloatText();

		if (outNextChild != NULL)
		{
			mat = mat->NextSiblingElement();
			*outNextChild = Create(mat, document);
		}

		return val;
	}

	ReadNode ReadNode::next()
	{
		ReadNode node;

		node.document = document;
		node.element = element->NextSiblingElement();
		if (node.element == NULL)
		{
			node.bEmpty = true;
			return node;
		}

		node.name = node.element->Name();

		return node;
	}

	ReadNode ReadNode::firstChild()
	{
		ReadNode node;

		node.document = document;
		node.element = element->FirstChildElement();
		if (node.element == NULL)
		{
			node.bEmpty = true;
			return node;
		}

		node.name = node.element->Name();

		return node;
	}

	void ReadNode::iteratorStart()
	{
		currentChildNode = new ReadNode();
		*currentChildNode = this->firstChild();
	}

	ReadNode ReadNode::iteratorChild()
	{
		ReadNode iter = *currentChildNode;
		if (iter.isEmpty() == false)
			*currentChildNode = iter.next();

		return iter;
	}

	void ReadNode::iteratorEnd()
	{
		delete currentChildNode; currentChildNode = 0;
	}

	string ReadNode::getType()
	{
		if (element->FirstAttribute() == NULL)
			return "";
		string type = element->FirstAttribute()->Value();
		return type;
	}

	ReadNode ReadNode::Create(Xml::XMLElement * e, Xml::XMLDocument * d)
	{
		ReadNode node;
		node.element = e;
		node.document = d;
		if (node.element == NULL)
			node.bEmpty = true;
		else
			node.name = node.element->Name();

		return node;
	}

}