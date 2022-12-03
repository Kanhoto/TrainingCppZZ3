/* *********************************************************************************************************************
 * Project name: mock_exam
 * File name   : main_tests
 * Author      : Damien Nguyen
 * Date        : Sunday, November 27, 2022 
 * ********************************************************************************************************************/

#include <sstream>
#include "product.hpp"

static unsigned constructs {};
static unsigned copies {};
static unsigned transfers {};

TEST_CASE("1 - Constructions and assignments") {
    Book b1 { "Title", "Author" };
    Book b10 { "Les fleurs du mal", "Victor Hugo" };

    REQUIRE(Product::constructs() == (constructs += 2));
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == transfers);

    auto b2 { b1 };
    REQUIRE(Product::constructs() == ++constructs);
    REQUIRE(Product::copies() == ++copies);
    REQUIRE(Product::transfers() == transfers);

    auto b3 { std::move(b2) };
    REQUIRE(Product::constructs() == ++constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == ++transfers);

    b2 = b3;
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == ++copies);
    REQUIRE(Product::transfers() == transfers);

    b3 = std::move(b2);
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == ++transfers);

    b3 = b3;
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == transfers);

    b3 = std::move(b3);
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == transfers);

    b10 = b1;
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == ++copies);
    REQUIRE(Product::transfers() == transfers);
    REQUIRE(b10.name() == "Title");
    REQUIRE(b10.author() == "Author");

    b10 = { "Les fleurs du mal", "Victor Hugo" };
    REQUIRE(Product::constructs() == ++constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == ++transfers);
    REQUIRE(b10.name() == "Les fleurs du mal");
    REQUIRE(b10.author() == "Victor Hugo");

    b10 = std::move(b1);
    REQUIRE(Product::constructs() == constructs);
    REQUIRE(Product::copies() == copies);
    REQUIRE(Product::transfers() == ++transfers);
    REQUIRE(b10.name() == "Title");
    REQUIRE(b10.author() == "Author");
}

/*TEST_CASE("2 - Inheritance") {
    auto book_ptr { std::make_unique<Book>("Title", "Author") };
    auto pen_ptr { std::make_unique<Item>("Pen") };

    Product* b1 = book_ptr.get();
    Product* b2 = pen_ptr.get();

    std::stringstream ss1;
    b1->display(ss1);
    REQUIRE(ss1.str() == "Book { name = Title, author = Author, price = 10 }");

    std::stringstream ss2;
    b2->display(ss2);
    REQUIRE(ss2.str() == "Item { name = Pen, price = 10 }");
}*/

/*TEST_CASE("3 - Operators") {
    PriceRange r1 {};
    PriceRange r2 { 0, 10 };
    PriceRange r3 { 3, 9 };
    PriceRange r4 {};

    REQUIRE(r1 < r2);
    REQUIRE(r2 < r3);
    REQUIRE(r1 == r4);
    REQUIRE(r1 != r2);
}*/

/*TEST_CASE("4 - Functor") {
    auto ranges { PriceRangeGenerator<5, 10, 3> {}() };

    REQUIRE(ranges.size() == 3);
    REQUIRE(ranges[0] == PriceRange { 10, 14 });
    REQUIRE(ranges[1] == PriceRange { 15, 19 });
    REQUIRE(ranges[2] == PriceRange { 20, 24 });
}*/

/*TEST_CASE("5 - Exception") {
    int         errors {};
    Store<Item> store;

    try {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
        [[maybe_unused]] auto count { store.count_items({}) };
#pragma clang diagnostic pop
    } catch (const std::exception& ex) {
        ++errors;
    }

    REQUIRE(errors == 1);
}*/

/*TEST_CASE("6 - Multimap manipulation (add keys and items)") {
    Store<Item> store;
    PriceRange  r1 { 0, 9 };

    REQUIRE(store.count_items() == 0);

    auto ranges { PriceRangeGenerator<10, 0, 2> {}() };
    std::for_each(ranges.begin(), ranges.end(), [&store](auto& range) {
        store.add_key(range);
    });

    store.add_item(std::make_unique<Item>("Pen", 5));
    REQUIRE(store.count_items() == 1);
    REQUIRE(store.count_items(r1) == 1);

    store.add_item(std::make_unique<Item>("Notepad", 14));
    REQUIRE(store.count_keys() == 2);
    REQUIRE(store.count_items() == 2);
    REQUIRE(store.count_items({ 10, 19 }) == 1);
}*/

/*TEST_CASE("7 - Multimap manipulation (remove keys and items)") {
    Store<Item> store;

    auto ranges { PriceRangeGenerator<10, 0, 2> {}() };
    std::for_each(ranges.begin(), ranges.end(), [&store](auto& range) {
        store.add_key(range);
    });

    store.add_key({ 10, 19 });
    store.add_key({ 10, 19 });
    store.add_key({ 10, 19 });
    store.add_item(std::make_unique<Item>("Pen", 5));
    store.add_item(std::make_unique<Item>("Notepad", 14));

    store.remove_item("Notepad");
    REQUIRE(store.count_keys() == 5);
    REQUIRE(store.count_items() == 1);
    REQUIRE(store.count_items({ 10, 19 }) == 0);

    store.remove_key(10, 19);
    REQUIRE(store.count_keys() == 1);
    REQUIRE(store.count_items() == 1);
}*/

/*TEST_CASE("8 - Stream output operator") {
    Store<Item> store;

    auto ranges { PriceRangeGenerator<10, 0, 2> {}() };
    std::for_each(ranges.begin(), ranges.end(), [&store](auto& range) {
        store.add_key(range);
    });

    store.add_item(std::make_unique<Item>("Pen", 5));

    store.add_key({ 10, 19 });
    store.add_key({ 10, 19 });
    store.add_key({ 10, 19 });
    store.add_item(std::make_unique<Item>("Notepad", 14));

    std::string expected = "{\n"
                           "\t[0, 9]\n"
                           "\t\tItem { name = Pen, price = 5 }\n"
                           "\t[10, 19]\n"
                           "\t\tItem { name = Notepad, price = 14 }\n"
                           "\t[10, 19]\n"
                           "\t[10, 19]\n"
                           "\t[10, 19]\n"
                           "}";

    std::stringstream ss;
    ss << store;
    REQUIRE(ss.str() == expected);
}*/
