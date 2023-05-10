import java.util.ArrayList;
import java.util.Stack;

public class PlaylistTree {

	public PlaylistNode primaryRoot; // root of the primary B+ tree
	public PlaylistNode secondaryRoot; // root of the secondary B+ tree

	public PlaylistTree(Integer order) {
		PlaylistNode.order = order;
		primaryRoot = new PlaylistNodePrimaryLeaf(null);
		primaryRoot.level = 0;

		secondaryRoot = new PlaylistNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addSong(CengSong song) {
		addSongPrimary(song);
		addSongSecondary(song);
	}

	public CengSong searchSong(Integer audioId) {
		// find the song with the searched audioId in primary B+ tree
		// return value will not be tested, just print according to the specifications
		PlaylistNode node = primaryRoot;
		boolean find;
		int tab = 0;

		while (node.getType() == PlaylistNodeType.Internal) {
			System.out.println("\t".repeat(tab) + "<index>");
			for (int i = 0; i < ((PlaylistNodePrimaryIndex) node).audioIdCount(); i++) {
				System.out.println("\t".repeat(tab) + ((PlaylistNodePrimaryIndex) node).audioIdAtIndex(i));
			}
			System.out.println("\t".repeat(tab) + "</index>");

			find = false;
			for (int i = 0; i < ((PlaylistNodePrimaryIndex) node).audioIdCount(); i++) {
				if (((PlaylistNodePrimaryIndex) node).audioIdAtIndex(i) > audioId) {
					node = ((PlaylistNodePrimaryIndex) node).getChildrenAt(i);
					find = true;
					break;
				}
			}
			if (!find)
				node = ((PlaylistNodePrimaryIndex) node)
						.getChildrenAt(((PlaylistNodePrimaryIndex) node).audioIdCount());

			tab++;
		}

		for (int i = 0; i < ((PlaylistNodePrimaryLeaf) node).songCount(); i++) {
			if (((PlaylistNodePrimaryLeaf) node).songAtIndex(i).audioId() == audioId) {
				System.out.println("\t".repeat(tab) + "<data>");
				System.out.println("\t".repeat(tab) + "<record>"
						+ ((PlaylistNodePrimaryLeaf) node).songAtIndex(i).fullName() + "</record>");
				System.out.println("\t".repeat(tab) + "</data>");
				return (((PlaylistNodePrimaryLeaf) node).songAtIndex(i));
			}
		}

		System.out.println("Could not find " + audioId);
		return null;
	}

	public void printPrimaryPlaylist() {
		// print the primary B+ tree in Depth-first order
		Stack<PlaylistNode> itemStack = new Stack<PlaylistNode>();
		Stack<Integer> tabStack = new Stack<Integer>();
		PlaylistNode root = primaryRoot;

		itemStack.add(root);
		tabStack.add(0);

		while (!itemStack.isEmpty()) {
			PlaylistNode node = itemStack.pop();
			int tabCount = tabStack.pop();

			// if node is an internal node
			if (node.getType() == PlaylistNodeType.Internal) {
				ArrayList<PlaylistNode> children = ((PlaylistNodePrimaryIndex) node).getAllChildren();
				for (int i = children.size() - 1; i >= 0; i--) {
					itemStack.add(children.get(i));
					tabStack.add(tabCount + 1);
				}

				// Print keys all auidoIds on this internal node
				System.out.println("\t".repeat(tabCount) + "<index>");
				for (int i = 0; i < ((PlaylistNodePrimaryIndex) node).audioIdCount(); i++) {
					System.out.println("\t".repeat(tabCount) + ((PlaylistNodePrimaryIndex) node).audioIdAtIndex(i));
				}
				System.out.println("\t".repeat(tabCount) + "</index>");
			}

			else if (node.getType() == PlaylistNodeType.Leaf) {
				System.out.println("\t".repeat(tabCount) + "<data>");
				for (int i = 0; i < ((PlaylistNodePrimaryLeaf) node).songCount(); i++) {
					System.out.println("\t".repeat(tabCount) + "<record>"
							+ ((PlaylistNodePrimaryLeaf) node).songAtIndex(i).fullName() + "</record>");
				}
				System.out.println("\t".repeat(tabCount) + "</data>");
			}
		}
		return;
	}

	public void printSecondaryPlaylist() {
		// print the secondary B+ tree in Depth-first order
		Stack<PlaylistNode> itemStack = new Stack<PlaylistNode>();
		Stack<Integer> tabStack = new Stack<Integer>();
		PlaylistNode root = secondaryRoot;

		itemStack.add(root);
		tabStack.add(0);

		while (!itemStack.isEmpty()) {
			PlaylistNode node = itemStack.pop();
			int tabCount = tabStack.pop();

			// if node is an internal node
			if (node.getType() == PlaylistNodeType.Internal) {
				ArrayList<PlaylistNode> children = ((PlaylistNodeSecondaryIndex) node).getAllChildren();
				for (int i = children.size() - 1; i >= 0; i--) {
					itemStack.add(children.get(i));
					tabStack.add(tabCount + 1);
				}

				// print keys all keys on this internal node
				System.out.println("\t".repeat(tabCount) + "<index>");
				for (int i = 0; i < ((PlaylistNodeSecondaryIndex) node).genreCount(); i++) {
					System.out.println("\t".repeat(tabCount) + ((PlaylistNodeSecondaryIndex) node).genreAtIndex(i));
				}
				System.out.println("\t".repeat(tabCount) + "</index>");
			}

			else if (node.getType() == PlaylistNodeType.Leaf) {
				System.out.println("\t".repeat(tabCount) + "<data>");
				for (int i = 0; i < ((PlaylistNodeSecondaryLeaf) node).genreCount(); i++) {
					System.out.println("\t".repeat(tabCount) + ((PlaylistNodeSecondaryLeaf) node).genreAtIndex(i));
					for (int j = 0; j < ((PlaylistNodeSecondaryLeaf) node).songsAtIndex(i).size(); j++) {
						System.out.println("\t".repeat(tabCount + 1) + "<record>"
								+ ((PlaylistNodeSecondaryLeaf) node).songsAtIndex(i).get(j).fullName() + "</record>");
					}
				}
				System.out.println("\t".repeat(tabCount) + "</data>");
			}
		}
		return;
	}

	// Extra functions if needed

	private void addSongPrimary(CengSong song) {

		// Find Primary index
		PlaylistNode node = primaryRoot;
		boolean find;
		while (node.getType() == PlaylistNodeType.Internal) {
			find = false;
			for (int index = 0; index < ((PlaylistNodePrimaryIndex) node).audioIdCount(); index++) {
				// if ith key is greater than our key, then i is the index of next child
				if (((PlaylistNodePrimaryIndex) node).audioIdAtIndex(index) > song.audioId()) {
					node = ((PlaylistNodePrimaryIndex) node).getChildrenAt(index);
					find = true;
					break;
				}
			}
			// If not find it is last node
			if (!find)
				node = ((PlaylistNodePrimaryIndex) node)
						.getChildrenAt(((PlaylistNodePrimaryIndex) node).audioIdCount());
		}

		// Primary B+Tree
		PlaylistNodePrimaryLeaf leafToInsertPrimary = ((PlaylistNodePrimaryLeaf) node);
		Integer indexToInsert = leafToInsertPrimary.songCount();
		Integer maxCount = (2 * PlaylistNode.order + 1);

		for (int index = 0; index < leafToInsertPrimary.songCount(); index++) {
			if (leafToInsertPrimary.audioIdAtIndex(index) > song.audioId()) {
				indexToInsert = index;
				break;
			}
		}

		// Insert song to the tree
		leafToInsertPrimary.addSong(indexToInsert, song);

		// If leaf is a root
		if (leafToInsertPrimary.getParent() == null) {
			// If overflow in root
			if (leafToInsertPrimary.songCount() == maxCount) {

				PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null);
				PlaylistNodePrimaryLeaf newNode = new PlaylistNodePrimaryLeaf(newRoot);

				for (int oldIndex = PlaylistNode.order,
						newIndex = 0; oldIndex < leafToInsertPrimary.songCount(); oldIndex++, newIndex++)
					newNode.addSong(newIndex, leafToInsertPrimary.songAtIndex(oldIndex));

				leafToInsertPrimary.getSongs().subList(PlaylistNode.order, leafToInsertPrimary.getSongs().size())
						.clear();
				leafToInsertPrimary.setParent(newRoot);

				newRoot.addAudioId(0, newNode.songAtIndex(0).audioId());
				newRoot.addChild(0, leafToInsertPrimary);
				newRoot.addChild(1, newNode);

				primaryRoot = newRoot;
			}
		}

		// Else leaf is not root
		else {

			// If overflow in node leaf
			if (leafToInsertPrimary.songCount() == maxCount) {

				// Divide node and fill them
				PlaylistNode parent = leafToInsertPrimary.getParent();
				PlaylistNodePrimaryLeaf newNode = new PlaylistNodePrimaryLeaf(parent);

				// Fill the newNode
				for (int oldIndex = PlaylistNode.order,
						newIndex = 0; oldIndex < leafToInsertPrimary.songCount(); oldIndex++, newIndex++)
					newNode.addSong(newIndex, leafToInsertPrimary.songAtIndex(oldIndex));

				// Remove excess data from old leaf node
				leafToInsertPrimary.getSongs().subList(PlaylistNode.order, leafToInsertPrimary.getSongs().size())
						.clear();

				// Add new leaf node to its internal parent node
				Integer audioIdToUp = newNode.songAtIndex(0).audioId();
				boolean setFlag = false;

				for (int index = 0; index < ((PlaylistNodePrimaryIndex) parent).audioIdCount(); index++) {
					if (((PlaylistNodePrimaryIndex) parent).audioIdAtIndex(index) > audioIdToUp) {
						((PlaylistNodePrimaryIndex) parent).addAudioId(index, audioIdToUp);
						((PlaylistNodePrimaryIndex) parent).addChild(index + 1, newNode);
						setFlag = true;
						break;
					}
				}

				if (!setFlag) {
					((PlaylistNodePrimaryIndex) parent).addAudioId(audioIdToUp);
					((PlaylistNodePrimaryIndex) parent).addChild(newNode);
				}

				// Check if overflow exists in leaf's Internal parent node
				PlaylistNode nextParent;
				while (((PlaylistNodePrimaryIndex) parent).audioIdCount() == maxCount) {
					setFlag = false;

					// Fetch parent of the internal parent node
					nextParent = parent.getParent();

					// If internal parent node is root
					if (nextParent == null) {
						PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null);
						PlaylistNodePrimaryIndex newInternalNode = new PlaylistNodePrimaryIndex(newRoot);

						// Fill the new internal node
						for (int oldIndex = PlaylistNode.order + 1,
								newIndex = 0; oldIndex < ((PlaylistNodePrimaryIndex) parent)
										.audioIdCount(); oldIndex++, newIndex++) {
							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addAudioId(newIndex,
									((PlaylistNodePrimaryIndex) parent).audioIdAtIndex(oldIndex));
							newInternalNode.addChild(newIndex,
									((PlaylistNodePrimaryIndex) parent).getChildrenAt(oldIndex));
							((PlaylistNodePrimaryIndex) parent).getChildrenAt(oldIndex).setParent(newInternalNode);
						}

						newInternalNode.addChild(newInternalNode.audioIdCount(), ((PlaylistNodePrimaryIndex) parent)
								.getChildrenAt(((PlaylistNodePrimaryIndex) parent).audioIdCount()));
						((PlaylistNodePrimaryIndex) parent)
								.getChildrenAt(((PlaylistNodePrimaryIndex) parent).audioIdCount())
								.setParent(newInternalNode);

						audioIdToUp = ((PlaylistNodePrimaryIndex) parent).audioIdAtIndex(PlaylistNode.order);

						// Remove excess data from old internal node
						((PlaylistNodePrimaryIndex) parent).getAudioIds()
								.subList(PlaylistNode.order, ((PlaylistNodePrimaryIndex) parent).getAudioIds().size())
								.clear();
						((PlaylistNodePrimaryIndex) parent).getAllChildren().subList(PlaylistNode.order + 1,
								((PlaylistNodePrimaryIndex) parent).getAllChildren().size()).clear();

						// Connect both internal parent nodes to the newRoot
						newRoot.addAudioId(0, audioIdToUp);
						newRoot.addChild(0, parent);
						parent.setParent(newRoot);
						newRoot.addChild(1, newInternalNode);
						primaryRoot = newRoot;
						break;
					}

					// Else internal parent node is not a root
					else {

						// Create a new internal node
						PlaylistNodePrimaryIndex newInternalNode = new PlaylistNodePrimaryIndex(nextParent);

						// Fill the new internal node
						for (int oldIndex = PlaylistNode.order + 1,
								newIndex = 0; oldIndex < ((PlaylistNodePrimaryIndex) parent)
										.audioIdCount(); oldIndex++, newIndex++) {

							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addAudioId(newIndex,
									((PlaylistNodePrimaryIndex) parent).audioIdAtIndex(oldIndex));
							newInternalNode.addChild(newIndex,
									((PlaylistNodePrimaryIndex) parent).getChildrenAt(oldIndex));
							((PlaylistNodePrimaryIndex) parent).getChildrenAt(oldIndex).setParent(newInternalNode);
						}

						newInternalNode.addChild(newInternalNode.audioIdCount(), ((PlaylistNodePrimaryIndex) parent)
								.getChildrenAt(((PlaylistNodePrimaryIndex) parent).audioIdCount()));
						((PlaylistNodePrimaryIndex) parent)
								.getChildrenAt(((PlaylistNodePrimaryIndex) parent).audioIdCount())
								.setParent(newInternalNode);

						audioIdToUp = ((PlaylistNodePrimaryIndex) parent).audioIdAtIndex(PlaylistNode.order);

						// Remove additional items from old internal node
						((PlaylistNodePrimaryIndex) parent).getAudioIds()
								.subList(PlaylistNode.order, ((PlaylistNodePrimaryIndex) parent).getAudioIds().size())
								.clear();
						((PlaylistNodePrimaryIndex) parent).getAllChildren().subList(PlaylistNode.order + 1,
								((PlaylistNodePrimaryIndex) parent).getAllChildren().size()).clear();

						// Add new Internal parent node to its internal parent node
						for (int i = 0; i < ((PlaylistNodePrimaryIndex) nextParent).audioIdCount(); i++) {
							if (((PlaylistNodePrimaryIndex) nextParent).audioIdAtIndex(i) > audioIdToUp) {
								((PlaylistNodePrimaryIndex) nextParent).addAudioId(i, audioIdToUp);
								((PlaylistNodePrimaryIndex) nextParent).addChild(i, parent);

								// Need to set child, child added to start and it was pointing to parent
								((PlaylistNodePrimaryIndex) nextParent).setChild(i + 1, newInternalNode);
								setFlag = true;
								break;
							}
						}

						if (!setFlag) {
							((PlaylistNodePrimaryIndex) nextParent).addAudioId(audioIdToUp);

							// No need to set child child added to the end and it was pointing nothing
							((PlaylistNodePrimaryIndex) nextParent).addChild(newInternalNode);
						}
						parent = nextParent;
					}
				}
			}
		}
	}

	private void addSongSecondary(CengSong song) {

		// Find Secondary index
		PlaylistNode node = secondaryRoot;
		boolean find;
		while (node.getType() == PlaylistNodeType.Internal) {
			find = false;
			for (int index = 0; index < ((PlaylistNodeSecondaryIndex) node).genreCount(); index++) {
				if (((PlaylistNodeSecondaryIndex) node).genreAtIndex(index).compareTo(song.genre()) > 0) {
					node = ((PlaylistNodeSecondaryIndex) node).getChildrenAt(index);
					find = true;
					break;
				}
			}

			// If not find it is last node
			if (!find)
				node = ((PlaylistNodeSecondaryIndex) node)
						.getChildrenAt(((PlaylistNodeSecondaryIndex) node).genreCount());
		}

		// Secondary B+Tree
		PlaylistNodeSecondaryLeaf leafToInsertSecondary = ((PlaylistNodeSecondaryLeaf) node);
		Integer indexToInsertSecond = leafToInsertSecondary.genreCount();
		Integer maxCount = (2 * PlaylistNode.order + 1);
		boolean exist = false;

		for (int index = 0; index < leafToInsertSecondary.genreCount(); index++) {
			// If genres are equal add song bucket and do nothing
			if (leafToInsertSecondary.genreAtIndex(index).compareTo(song.genre()) == 0) {
				// Insert song to the convinient leaf if genre exists before
				leafToInsertSecondary.addSong(index, song);
				exist = true;
				break;
			}

			// Else find an index for insert
			else if (leafToInsertSecondary.genreAtIndex(index).compareTo(song.genre()) > 0) {
				indexToInsertSecond = index;
				break;
			}
		}

		// Insert song to the tree if genre does not exist before
		if (!exist)
			leafToInsertSecondary.addSong(indexToInsertSecond, song);

		// If leaf is a root
		if (leafToInsertSecondary.getParent() == null && !exist) {

			// If overflow in root (leaf)
			if (leafToInsertSecondary.genreCount() == maxCount) {
				PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null);
				PlaylistNodeSecondaryLeaf newNode = new PlaylistNodeSecondaryLeaf(newRoot);
				for (int oldIndex = PlaylistNode.order,
						newIndex = 0; oldIndex < leafToInsertSecondary.genreCount(); oldIndex++, newIndex++) {
					for (int count = 0; count < leafToInsertSecondary.songsAtIndex(oldIndex).size(); count++) {
						newNode.addSong(newIndex, leafToInsertSecondary.songsAtIndex(oldIndex).get(count));
					}
				}

				leafToInsertSecondary.getSongBucket()
						.subList(PlaylistNode.order, leafToInsertSecondary.getSongBucket().size()).clear();
				leafToInsertSecondary.setParent(newRoot);

				newRoot.addGenre(0, newNode.genreAtIndex(0));
				newRoot.addChild(0, leafToInsertSecondary);
				newRoot.addChild(1, newNode);
				secondaryRoot = newRoot;
			}
		}

		// Else leaf is not root
		else if (!exist) {
			// If overflow in root (leaf)
			if (leafToInsertSecondary.genreCount() == maxCount) {

				// Divide node into two and fill them
				PlaylistNode parent = leafToInsertSecondary.getParent();
				PlaylistNodeSecondaryLeaf newNode = new PlaylistNodeSecondaryLeaf(parent);
				for (int oldindex = PlaylistNode.order,
						newIndex = 0; oldindex < leafToInsertSecondary.genreCount(); oldindex++, newIndex++) {
					for (int k = 0; k < leafToInsertSecondary.songsAtIndex(oldindex).size(); k++) {
						newNode.addSong(newIndex, leafToInsertSecondary.songsAtIndex(oldindex).get(k));
					}
				}

				// Remove excess data from old leaf node
				leafToInsertSecondary.getSongBucket()
						.subList(PlaylistNode.order, leafToInsertSecondary.getSongBucket().size()).clear();

				// Add new leaf node to its internal parent node
				String genreToUp = newNode.genreAtIndex(0);
				boolean setFlag = false;

				for (int i = 0; i < ((PlaylistNodeSecondaryIndex) parent).genreCount(); i++) {
					// if entry can be sorted according to genre
					if (((PlaylistNodeSecondaryIndex) parent).genreAtIndex(i).compareTo(genreToUp) > 0) {
						((PlaylistNodeSecondaryIndex) parent).addGenre(i, genreToUp);
						((PlaylistNodeSecondaryIndex) parent).addChild(i + 1, newNode);
						setFlag = true;
						break;
					}
				}

				if (!setFlag) {
					((PlaylistNodeSecondaryIndex) parent).addGenre(genreToUp);
					((PlaylistNodeSecondaryIndex) parent).addChild(newNode);
				}

				PlaylistNode nextParent;
				while (((PlaylistNodeSecondaryIndex) parent).genreCount() == maxCount) {
					setFlag = false;

					// Fetch parent of the internal parent
					nextParent = parent.getParent();

					// If internal parent node is root
					if (nextParent == null) {
						PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null);
						PlaylistNodeSecondaryIndex newInternalNode = new PlaylistNodeSecondaryIndex(newRoot);

						// Fill new internal node
						for (int oldIndex = PlaylistNode.order + 1,
								newIndex = 0; oldIndex < ((PlaylistNodeSecondaryIndex) parent)
										.genreCount(); oldIndex++, newIndex++) {

							// Here, parent refers to old internal node (sibling of new internal node )
							newInternalNode.addGenre(newIndex,
									((PlaylistNodeSecondaryIndex) parent).genreAtIndex(oldIndex));
							newInternalNode.addChild(newIndex,
									((PlaylistNodeSecondaryIndex) parent).getChildrenAt(oldIndex));
							((PlaylistNodeSecondaryIndex) parent).getChildrenAt(oldIndex).setParent(newInternalNode);

						}

						newInternalNode.addChild(newInternalNode.genreCount(), ((PlaylistNodeSecondaryIndex) parent)
								.getChildrenAt(((PlaylistNodeSecondaryIndex) parent).genreCount()));
						((PlaylistNodeSecondaryIndex) parent)
								.getChildrenAt(((PlaylistNodeSecondaryIndex) parent).genreCount())
								.setParent(newInternalNode);

						genreToUp = ((PlaylistNodeSecondaryIndex) parent).genreAtIndex(PlaylistNode.order);

						// Remove additional items from old internal node
						((PlaylistNodeSecondaryIndex) parent).getAllGenres().subList(PlaylistNode.order,
								((PlaylistNodeSecondaryIndex) parent).getAllGenres().size()).clear();
						((PlaylistNodeSecondaryIndex) parent).getAllChildren().subList(PlaylistNode.order + 1,
								((PlaylistNodeSecondaryIndex) parent).getAllChildren().size()).clear();

						// Connect to both internal parent nodes to the newRoot
						newRoot.addGenre(0, genreToUp);
						newRoot.addChild(0, parent);
						parent.setParent(newRoot);
						newRoot.addChild(1, newInternalNode);
						secondaryRoot = newRoot;
						break;
					}

					// If Internal parent node is an ordinary index node
					else {

						// Create a new internal node
						PlaylistNodeSecondaryIndex newInternalNode = new PlaylistNodeSecondaryIndex(nextParent);

						// Fill new internal node
						for (int oldIndex = PlaylistNode.order + 1,
								newIndex = 0; oldIndex < ((PlaylistNodeSecondaryIndex) parent)
										.genreCount(); oldIndex++, newIndex++) {

							// Here, parent refers to old internal node (sibling of newInternalNode)
							newInternalNode.addGenre(newIndex,
									((PlaylistNodeSecondaryIndex) parent).genreAtIndex(oldIndex));
							newInternalNode.addChild(newIndex,
									((PlaylistNodeSecondaryIndex) parent).getChildrenAt(oldIndex));
							((PlaylistNodeSecondaryIndex) parent).getChildrenAt(oldIndex).setParent(newInternalNode);
						}

						newInternalNode.addChild(newInternalNode.genreCount(), ((PlaylistNodeSecondaryIndex) parent)
								.getChildrenAt(((PlaylistNodeSecondaryIndex) parent).genreCount()));
						((PlaylistNodeSecondaryIndex) parent)
								.getChildrenAt(((PlaylistNodeSecondaryIndex) parent).genreCount())
								.setParent(newInternalNode);

						genreToUp = ((PlaylistNodeSecondaryIndex) parent).genreAtIndex(PlaylistNode.order);

						// Remove additional items from old internal node
						((PlaylistNodeSecondaryIndex) parent).getAllGenres().subList(PlaylistNode.order,
								((PlaylistNodeSecondaryIndex) parent).getAllGenres().size()).clear();
						((PlaylistNodeSecondaryIndex) parent).getAllChildren().subList(PlaylistNode.order + 1,
								((PlaylistNodeSecondaryIndex) parent).getAllChildren().size()).clear();

						// Add new Internal parent node to its internal parent node
						for (int index = 0; index < ((PlaylistNodeSecondaryIndex) nextParent).genreCount(); index++) {

							// If entry can be sorted according to year
							if (((PlaylistNodeSecondaryIndex) nextParent).genreAtIndex(index)
									.compareTo(genreToUp) > 0) {
								((PlaylistNodeSecondaryIndex) nextParent).addGenre(index, genreToUp);
								((PlaylistNodeSecondaryIndex) nextParent).addChild(index, parent);

								// Need to set child child is added to start and it was pointing to parent
								((PlaylistNodeSecondaryIndex) nextParent).setChild(index + 1, newInternalNode);
								setFlag = true;
								break;
							}
						}
						if (!setFlag) {
							((PlaylistNodeSecondaryIndex) nextParent).addGenre(genreToUp);
							// No Need to set child child is added to the end and it was pointing nothing
							((PlaylistNodeSecondaryIndex) nextParent).addChild(newInternalNode);
						}
						parent = nextParent;
					}
				}
			}
		}
	}
}
