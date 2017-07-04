#include "product.h"

Product::Product() : productId(0), instockQuantity(0), price(0)
{
}

int Product::getProductId() const
{
    return productId;
}

void Product::setProductId(int productId)
{
    this->productId = productId;
}

double Product::getPrice() const
{
    return price;
}

void Product::setPrice(double price)
{
    this->price = price;
}

QString Product::getName() const
{
    return name;
}

void Product::setName(const QString &name)
{
    this->name = name;
}

QString Product::getPicture() const
{
    return picture;
}

void Product::setPicture(const QString &picture)
{
    this->picture = picture;
}

QString Product::getDescription() const
{
    return description;
}

void Product::setDescription(const QString &description)
{
    this->description = description;
}

QString Product::getKind() const
{
    return kind;
}

void Product::setKind(const QString &kind)
{
    this->kind = kind;
}

int Product::getInstockQuantity() const
{
    return instockQuantity;
}

void Product::setInstockQuantity(int instockQuantity)
{
    this->instockQuantity = instockQuantity;
}

QVariantList Product::object2VariantList()
{
    QVariantList variantList;
    variantList << productId << price << name << picture << description << instockQuantity << kind;
    return variantList;
}

