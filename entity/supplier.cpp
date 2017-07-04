#include "supplier.h"

Supplier::Supplier() : supplierId(0)
{
}

Supplier::~Supplier()
{
}

int Supplier::getSupplierId() const
{
    return supplierId;
}

void Supplier::setSupplierId(const int supplier_id)
{
    this->supplierId = supplier_id;
}

QString Supplier::getName() const
{
    return name;
}

void Supplier::setName(const QString &name)
{
    this->name = name;
}

QString Supplier::getAddress() const
{
    return address;
}

void Supplier::setAddress(const QString &address)
{
    this->address = address;
}

QString Supplier::getPhone() const
{
    return phone;
}

void Supplier::setPhone(const QString &phone)
{
    this->phone = phone;
}

QString Supplier::getDescription() const
{
    return description;
}

void Supplier::setDescription(const QString &description)
{
    this->description = description;
}

QVariantList Supplier::object2VariantList()
{
    QVariantList i;
    i << name << phone << picutre << supplierId << address << description;
    return i;
}

QString Supplier::getPicutre() const
{
    return picutre;
}

void Supplier::setPicutre(const QString &picutre)
{
    this->picutre = picutre;
}
