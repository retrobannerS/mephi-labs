#include "trees/N_ary_tree.hpp"
#include "gtest/gtest.h"

using namespace lab4;

TEST(N_ary_tree, constructor) {
    //arrange&act
    N_ary_tree<char> tree('I', 3);
    //assert
    EXPECT_EQ(tree.value(), 'I');
    EXPECT_EQ(tree.arity(), 3);
    EXPECT_EQ(tree.current_subtrees(), 0);
    EXPECT_EQ(tree.size(), 1);
}

TEST(N_ary_tree, CopyConstructor) {
    //arrange
    N_ary_tree<char> tree('I', 3);
    tree.add_subtree('J');
    tree.add_subtree('K');
    tree.add_subtree('L');
    tree[0].add_subtree('A');
    tree[0].add_subtree('B');
    tree[1].add_subtree('C');
    //act
    N_ary_tree<char> tree2(tree);
    N_ary_tree<char> tree3 = tree;
    //assert
    EXPECT_EQ(tree2.value(), 'I');
    EXPECT_EQ(tree2.arity(), 3);
    EXPECT_EQ(tree2.current_subtrees(), 3);
    EXPECT_EQ(tree2.size(), 7);
    EXPECT_EQ(tree2[0].value(), 'J');
    EXPECT_EQ(tree2[0].arity(), 3);
    EXPECT_EQ(tree2[0].current_subtrees(), 2);
    EXPECT_EQ(tree2[0].size(), 3);
    EXPECT_EQ(tree2[0][0].value(), 'A');
    EXPECT_EQ(tree2[0][0].arity(), 3);
    EXPECT_EQ(tree2[0][0].current_subtrees(), 0);
    EXPECT_EQ(tree2[0][0].size(), 1);
    EXPECT_EQ(tree2[0][1].value(), 'B');
    EXPECT_EQ(tree2[0][1].arity(), 3);
    EXPECT_EQ(tree2[0][1].current_subtrees(), 0);
    EXPECT_EQ(tree2[0][1].size(), 1);
    EXPECT_EQ(tree2[1].value(), 'K');
    EXPECT_EQ(tree2[1].arity(), 3);
    EXPECT_EQ(tree2[1].current_subtrees(), 1);
    EXPECT_EQ(tree2[1].size(), 2);
    EXPECT_EQ(tree2[1][0].value(), 'C');
    EXPECT_EQ(tree2[1][0].arity(), 3);
    EXPECT_EQ(tree2[1][0].current_subtrees(), 0);
    EXPECT_EQ(tree2[1][0].size(), 1);
    EXPECT_EQ(tree2[2].value(), 'L');
    EXPECT_EQ(tree2[2].arity(), 3);
    EXPECT_EQ(tree2[2].current_subtrees(), 0);
    EXPECT_EQ(tree2[2].size(), 1);
    EXPECT_EQ(tree2, tree3);
}

TEST(N_ary_tree, Destructor) {
    //arrange
    auto *tree = new N_ary_tree<char>('I', 3);
    tree->add_subtree('J');
    tree->add_subtree('K');
    tree->add_subtree('L');
    (*tree)[0].add_subtree('A');
    (*tree)[0].add_subtree('B');
    (*tree)[1].add_subtree('C');
    //act
    delete tree;
    //assert
    EXPECT_TRUE(true);
}

TEST(N_ary_tree, Arity) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    int arity = tree.arity();

    // Assert
    EXPECT_EQ(arity, 3);
}

TEST(N_ary_tree, CurrentSubtrees) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);

    // Act
    int currentSubtrees = tree.current_subtrees();

    // Assert
    EXPECT_EQ(currentSubtrees, 2);
}

TEST(N_ary_tree, CurrentSubtrees_EmptyTree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    int currentSubtrees = tree.current_subtrees();

    // Assert
    EXPECT_EQ(currentSubtrees, 0);
}

TEST(N_ary_tree, Size) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);

    // Act
    int size = tree.size();

    // Assert
    EXPECT_EQ(size, 3);
}

TEST(N_ary_tree, Size_EmptySubTrees) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    int size = tree.size();

    // Assert
    EXPECT_EQ(size, 1);
}

TEST(N_ary_tree, Height) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree[0].add_subtree(4);

    // Act
    int height = tree.height();

    // Assert
    EXPECT_EQ(height, 3);
}

TEST(N_ary_tree, Height_EmptyTree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    int height = tree.height();

    // Assert
    EXPECT_EQ(height, 1);
}

TEST(N_ary_tree, Value) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    int value = tree.value();

    // Assert
    EXPECT_EQ(value, 1);
}

TEST(N_ary_tree, SubTree_value) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);

    // Act
    int value = tree[0].value();
    int value2 = tree[1].value();

    // Assert
    EXPECT_EQ(value, 2);
    EXPECT_EQ(value2, 3);
}

TEST(N_ary_tree, Set) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    tree.set(2);
    int value = tree.value();

    // Assert
    EXPECT_EQ(value, 2);
}

TEST(N_ary_tree, SubTree_set) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);

    // Act
    tree[0].set(4);
    tree[1].set(5);
    int value = tree[0].value();
    int value2 = tree[1].value();

    // Assert
    EXPECT_EQ(value, 4);
    EXPECT_EQ(value2, 5);
}

TEST(N_ary_tree, AddSubtree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    auto* subtree = new N_ary_tree<int>(2, 3);

    // Act
    tree.add_subtree(subtree);

    // Assert
    EXPECT_EQ(tree.current_subtrees(), 1);
    EXPECT_EQ(tree.get_subtree(0).value(), 2);
    delete subtree;
}

TEST(N_ary_tree, AddSubtree_MaxSubtreesExceeded) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act
    for (int i = 0; i < 3; i++) {
        tree.add_subtree(i + 2);
    }

    // Assert
    EXPECT_THROW(tree.add_subtree(5), std::out_of_range);
}

TEST(N_ary_tree, AddSubtree_DifferentArity) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    auto* subtree = new N_ary_tree<int>(2, 4);

    // Act & Assert
    EXPECT_THROW(tree.add_subtree(subtree), std::invalid_argument);
    delete subtree;
}

TEST(N_ary_tree, GetSubtree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);

    // Act
    N_ary_tree<int>& subtree = tree.get_subtree(0);

    // Assert
    EXPECT_EQ(subtree.value(), 2);
}

TEST(N_ary_tree, GetSubtree_OutOfRange) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act & Assert
    EXPECT_THROW(tree.get_subtree(0), std::out_of_range);
}

TEST(N_ary_tree, GetParent) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    N_ary_tree<int>& subtree = tree.get_subtree(0);

    // Act
    N_ary_tree<int>& parent = subtree.get_parent();

    // Assert
    EXPECT_EQ(parent.value(), 1);
}

TEST(N_ary_tree, GetParent_NoParent) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act & Assert
    EXPECT_THROW(tree.get_parent(), std::out_of_range);
}

TEST(N_ary_tree, DeleteSubtree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);

    // Act
    tree.delete_subtree(0);

    // Assert
    EXPECT_EQ(tree.current_subtrees(), 1);
    EXPECT_EQ(tree.get_subtree(0).value(), 3);
}

TEST(N_ary_tree, DeleteSubtree_OutOfRange) {
    // Arrange
    N_ary_tree<int> tree(1, 3);

    // Act & Assert
    EXPECT_THROW(tree.delete_subtree(0), std::out_of_range);
}

TEST(N_ary_tree, Simple_to_string) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree.to_string(), "1 2 3 4 ");
}

TEST(N_ary_tree, to_string_NLR) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree.to_string(N_ary_tree<int>::TraverseType::NLR), "1 2 3 4 ");
}

TEST(N_ary_tree, to_string_NRL) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree.to_string(N_ary_tree<int>::TraverseType::NRL), "1 4 3 2 ");
}

TEST(N_ary_tree, to_string_LRN) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree.to_string(N_ary_tree<int>::TraverseType::LRN), "2 3 4 1 ");
}

TEST(N_ary_tree, to_string_RLN) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree.to_string(N_ary_tree<int>::TraverseType::RLN), "4 3 2 1 ");
}

TEST(N_ary_tree, operator_brackets) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    EXPECT_EQ(tree[0].value(), 2);
    EXPECT_EQ(tree[1].value(), 3);
    EXPECT_EQ(tree[2].value(), 4);
}

TEST(N_ary_tree, map) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act
    N_ary_tree<int>* mapped_tree = tree.map([](int val){ return val * 2; });

    // Assert
    EXPECT_EQ(mapped_tree->value(), 2);
    EXPECT_EQ((*mapped_tree)[0].value(), 4);
    EXPECT_EQ((*mapped_tree)[1].value(), 6);
    EXPECT_EQ((*mapped_tree)[2].value(), 8);

    delete mapped_tree;
}

TEST(N_ary_tree, Where) {
    // Arrange
    N_ary_tree<int> tree(2, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act
    N_ary_tree<int>* filtered_tree = tree.where([](int val){ return val % 2 == 0; });

    // Assert
    EXPECT_EQ(filtered_tree->value(), 2);
    EXPECT_EQ(filtered_tree->size(), 3);
    EXPECT_EQ(filtered_tree->height(), 2);
    EXPECT_EQ((*filtered_tree)[0].value(), 2);
    EXPECT_EQ((*filtered_tree)[1].value(), 4);

    delete filtered_tree;
}

TEST(N_ary_tree, EmptyWhere) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act
    N_ary_tree<int>* filtered_tree = tree.where([](int val){ return val % 2 == 0; });

    // Assert
    EXPECT_EQ(filtered_tree, nullptr);
}

TEST(N_ary_tree, contains_item) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    ASSERT_TRUE(tree.contains(1));
    ASSERT_TRUE(tree.contains(2));
    ASSERT_TRUE(tree.contains(3));
    ASSERT_TRUE(tree.contains(4));
    ASSERT_FALSE(tree.contains(5));
}

TEST(N_ary_tree, contains_subtree) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    // Act & Assert
    N_ary_tree<int> subtree(2, 3);
    ASSERT_TRUE(tree.contains(subtree));

    N_ary_tree<int> non_subtree(5, 3);
    ASSERT_FALSE(tree.contains(non_subtree));
}

TEST(N_ary_tree, item_count) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(1);
    tree.add_subtree(2);
    tree.add_subtree(1);

    // Act & Assert
    ASSERT_EQ(tree.item_count(1), 3);
    ASSERT_EQ(tree.item_count(2), 1);
    ASSERT_EQ(tree.item_count(3), 0);
}

TEST(N_ary_tree, traverse_default) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    Sequence<int>* expected_seq = new ListSequence<int>();
    expected_seq->PushBack(1);
    expected_seq->PushBack(2);
    expected_seq->PushBack(3);
    expected_seq->PushBack(4);

    // Act
    Sequence<int> *seq = tree.traverse();

    for(int i = 0; i < tree.size(); i++)
        EXPECT_EQ((*seq)[i], (*expected_seq)[i]);

    delete expected_seq;
    delete seq;
}

TEST(N_ary_tree, traverse_NLR) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    Sequence<int>* expected_seq = new ListSequence<int>();
    expected_seq->PushBack(1);
    expected_seq->PushBack(2);
    expected_seq->PushBack(3);
    expected_seq->PushBack(4);

    // Act
    Sequence<int> *seq = tree.traverse(N_ary_tree<int>::TraverseType::NLR);

    for(int i = 0; i < tree.size(); i++)
        EXPECT_EQ((*seq)[i], (*expected_seq)[i]);
    delete expected_seq;
    delete seq;
}

TEST(N_ary_tree, traverse_NRL) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    Sequence<int>* expected_seq = new ListSequence<int>();
    expected_seq->PushBack(1);
    expected_seq->PushBack(4);
    expected_seq->PushBack(3);
    expected_seq->PushBack(2);

    // Act
    Sequence<int> *seq = tree.traverse(N_ary_tree<int>::TraverseType::NRL);

    // Assert
    for(int i = 0; i < tree.size(); i++)
        EXPECT_EQ((*seq)[i], (*expected_seq)[i]);
    delete expected_seq;
    delete seq;
}

TEST(N_ary_tree, traverse_LRN) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    Sequence<int>* expected_seq = new ListSequence<int>();
    expected_seq->PushBack(2);
    expected_seq->PushBack(3);
    expected_seq->PushBack(4);
    expected_seq->PushBack(1);

    // Act
    Sequence<int> *seq = tree.traverse(N_ary_tree<int>::TraverseType::LRN);

    // Assert
    for(int i = 0; i < tree.size(); i++)
        EXPECT_EQ((*seq)[i], (*expected_seq)[i]);
    delete expected_seq;
    delete seq;
}

TEST(N_ary_tree, traverse_RLN) {
    // Arrange
    N_ary_tree<int> tree(1, 3);
    tree.add_subtree(2);
    tree.add_subtree(3);
    tree.add_subtree(4);

    Sequence<int>* expected_seq = new ListSequence<int>();
    expected_seq->PushBack(4);
    expected_seq->PushBack(3);
    expected_seq->PushBack(2);
    expected_seq->PushBack(1);

    // Act
    Sequence<int> *seq = tree.traverse(N_ary_tree<int>::TraverseType::RLN);

    // Assert
    for(int i = 0; i < tree.size(); i++)
        EXPECT_EQ((*seq)[i], (*expected_seq)[i]);
    delete expected_seq;
    delete seq;
}
