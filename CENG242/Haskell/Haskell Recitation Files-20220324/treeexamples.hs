data Tree a = ETree | Node a (Tree a) (Tree a) deriving Show

-- insert :: (Ord k) => k -> v -> Tree (k,v) -> Tree (k,v)
insert k v ETree = Node (k,v) ETree ETree 
insert k v (Node (kt,vt) left right) | k < kt = Node (kt,vt) (insert k v left ) right
                                     | k > kt = Node (kt,vt) left (insert k v right)
                                     | otherwise = Node (k,v) left right

-- Exercise: enhance tmax to return (maxnode,remaining tree), update delete accordingly
tmax (Node n left ETree)  =  n
tmax (Node n left right)  =  tmax right

delete _ ETree = ETree
delete k (Node (kt,vt) left right) | k < kt = Node (kt,vt) (delete k left) right
                                   | k > kt = Node (kt,vt) left (delete k right)
                                   | otherwise = case (left, right) of
                                                  (ETree,ETree) -> ETree
                                                  (l,ETree) -> l
                                                  (ETree,r) -> r
                                                  (l,r) -> let maxnode = tmax l 
                                                           in  Node maxnode (delete (fst maxnode) left)  right

get _ ETree = Nothing
get k (Node (kt,vt) left right) | k < kt = get k left
                                | k > kt = get k right
                                | otherwise = Just vt

listtobst = foldl (\t -> \(a,b) ->  insert a b t) ETree  

bstree = insert 4 "a"  $ insert 20 "b"  $ insert 10 "c"  $ insert 12 "hasan"  $ insert 2 "mahmut"  $ insert 3 "ayse"  $ insert 5 "ali" ETree
bstree2 = listtobst ( zip [7,4,10,9,6,4,3,5,8,13,15,12,5,6,11] ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"])

-------------------- Priority queue

psize ETree = 0
psize (Node (_,_,n) _ _) = n

pinsert k v ETree = Node (k,v,1) ETree ETree
pinsert k v (Node (kt,vt,nel) left right)  | k < kt =
    if psize left < psize right then
        Node (k,v,nel+1) (pinsert kt vt left) right
    else
        Node (k,v,nel+1) left (pinsert kt vt right)
                                           | otherwise =
    if psize left < psize right then
        Node (kt,vt,nel+1) (pinsert k v left) right
    else
        Node (kt,vt,nel+1) left (pinsert k v right)
    
ppop ETree = error "empty"
ppop (Node (k,v,_) ETree ETree) = ((k,v) ,ETree)
ppop (Node (k,v,_) left ETree) = ((k,v),left)
ppop (Node (k,v,_) ETree right) = ((k,v),right)
ppop (Node node@(k,v,tsize) left right) = if pqkey left < pqkey right then
                                             let ((lk,lv), lremainder) =  ppop left
                                             in ((k,v),  Node (lk,lv,tsize-1) lremainder right) 
                                          else 
                                             let ((rk,rv), rremainder) =  ppop right
                                             in ((k,v), Node (rk,rv,tsize-1) left rremainder) where
            pqkey (Node (k,_,_) _ _) = k



pqtree = pinsert 4 "a"  $ pinsert 20 "b"  $ pinsert 10 "c"  $ pinsert 12 "hasan"  $ pinsert 2 "mahmut"  $ pinsert 3 "ayse"  $ pinsert 5 "ali" ETree

listtopq = foldl (\t -> \(a,b) ->  pinsert a b t) ETree 

popall ETree = []
popall pqtree = let (n,r) = ppop pqtree
                in n : popall r

pqtree2 = listtopq ( zip [7,4,10,9,6,4,3,5,8,13,15,12,5,6,11] ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"])

heapsort lst = popall $ listtopq lst

--data Return a = Success a | Failure
--data Maybe a = Just a | Nothing

-- get :: (Ord k) => k -> Tree (k,v) -> v
{--
get _ ETree = error "not found"
get k (Node (kt,vt) left right) | k < kt = get k left
                                | k > kt = get k right
                                | otherwise = vt
--}

-- pretty prints a tree. i.e. printtree pqtree2

printtree t = putStrLn (showPre " " " " "==" t) where
        showPre _ _ inn ETree = inn ++ "- []\n"
        showPre _ _ inn (Node nv ETree ETree) = inn ++ "- " ++
                    (show nv) ++ "\n"
        showPre first second inn (Node nv lt rt) =
            let newf = first ++ " |   "
                news = second ++ " |   "
                nullf = first ++ "     "
                nulls = second ++ "     "
                newinnf= first ++ " /----"
                newinns= second ++ " \\----"
            in (showPre nullf newf newinnf rt) ++
                newf ++ "\n" ++
                inn ++ "+ " ++ (show nv) ++  "\n" ++
                news ++ "\n" ++
                (showPre news nulls newinns lt)
