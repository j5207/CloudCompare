//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_ITEM_DELEGATE_HEADER
#define CC_ITEM_DELEGATE_HEADER

//qCC_db
#include <ccChunkedArray.h>

//Qt
#include <QStyledItemDelegate>

class ccHObject;
class ccGenericPointCloud;
class ccPolyline;
class ccGenericMesh;
class ccGenericPrimitive;
class ccOctree;
class ccKdTree;
class ccImage;
class ccCalibratedImage;
class ccGBLSensor;
class ccCameraSensor;
class ccMaterialSet;
class cc2DLabel;
class cc2DViewportObject;
class ccFacet;
class ccSensor;
class ccIndexedTransformationBuffer;
class CCShareable;

class QStandardItemModel;
class QStandardItem;
class QAbstractItemView;

//! GUI properties list dialog element
class ccPropertiesTreeDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:

	//! Delegate items roles
	enum CC_PROPERTY_ROLE { OBJECT_NO_PROPERTY		= 0				,
							OBJECT_NAME								,
							OBJECT_VISIBILITY						,
							OBJECT_CURRENT_DISPLAY					,
							OBJECT_COLORS_SHOWN						,
							OBJECT_NORMALS_SHOWN					,
							OBJECT_SCALAR_FIELD_SHOWN				,
							OBJECT_POLYLINE_WIDTH					,
							OBJECT_SENSOR_DRAW_FRUSTRUM				,
							OBJECT_SENSOR_DRAW_FRUSTRUM_PLANES		,
							OBJECT_SF_SHOW_SCALE					,
							OBJECT_OCTREE_LEVEL						,
							OBJECT_OCTREE_TYPE						,
							OBJECT_MESH_WIRE						,
							OBJECT_MESH_STIPPLING					,
							OBJECT_CURRENT_SCALAR_FIELD				,
							OBJECT_CURRENT_COLOR_RAMP				,
							OBJECT_IMAGE_ALPHA						,
							OBJECT_APPLY_IMAGE_VIEWPORT				,
							OBJECT_CLOUD_SF_EDITOR					,
							OBJECT_SENSOR_DISPLAY_SCALE				,
							OBJECT_COLOR_RAMP_STEPS					,
							OBJECT_MATERIALS						,
							OBJECT_APPLY_LABEL_VIEWPORT				,
							OBJECT_LABEL_DISP_2D					,
							OBJECT_LABEL_DISP_3D					,
							OBJECT_PRIMITIVE_PRECISION				,
							OBJECT_CLOUD_POINT_SIZE					,
							OBJECT_NAME_IN_3D						,
							OBJECT_FACET_CONTOUR					,
							OBJECT_FACET_MESH						,
							OBJECT_FACET_NORMAL_VECTOR				,
							OBJECT_SENSOR_INDEX						,
							OBJECT_SHOW_TRANS_BUFFER_PATH			,
							OBJECT_SHOW_TRANS_BUFFER_TRIHDERONS		,
							OBJECT_TRANS_BUFFER_TRIHDERONS_SCALE	,
	};

	//! Default constructor
	ccPropertiesTreeDelegate(QStandardItemModel* _model, QAbstractItemView* _view, QObject *parent = 0);

	//! Default destructor
	virtual ~ccPropertiesTreeDelegate();

	//inherited from QStyledItemDelegate
	virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index ) const;
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//virtual bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
	virtual void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void unbind();

	//! Fill property view with QItems corresponding to object's type
	void fillModel(ccHObject* hObject);

	//! Returns currently bound object
	ccHObject* getCurrentObject();

signals:
	void ccObjectPropertiesChanged(ccHObject* hObject) const;
	void ccObjectAppearanceChanged(ccHObject* hObject) const;
	void ccObjectAndChildrenAppearanceChanged(ccHObject* hObject) const;

protected slots:
	void updateItem(QStandardItem*);
	void scalarFieldChanged(int);
	void colorScaleChanged(int);
	void colorRampStepsChanged(int);
	void spawnColorRampEditor();
	void octreeDisplayTypeChanged(int);
	void octreeDisplayedLevelChanged(int);
	void primitivePrecisionChanged(int);
	void imageAlphaChanged(int);
	void applyImageViewport();
	void applyLabelViewport();
	void updateDisplay();
	void objectDisplayChanged(const QString &);
	void sensorScaleChanged(double);
	void sensorIndexChanged(double);
	void cloudPointSizeChanged(int);
	void polyineWidthChanged(int);
	void trihedronsScaleChanged(double);

protected:

	void addSeparator(QString title);
	void appendRow(QStandardItem* leftItem, QStandardItem* rightItem, bool openPersistentEditor = false);

	void fillWithHObject(ccHObject*);
	void fillWithPointCloud(ccGenericPointCloud*);
	void fillSFWithPointCloud(ccGenericPointCloud*);
	void fillWithMesh(ccGenericMesh*);
	void fillWithFacet(ccFacet*);
	void fillWithSensor(ccSensor*);
	void fillWithTransBuffer(ccIndexedTransformationBuffer*);
	void fillWithPolyline(ccPolyline*);
	void fillWithPrimitive(ccGenericPrimitive*);
	void fillWithPointOctree(ccOctree*);
	void fillWithPointKdTree(ccKdTree*);
	void fillWithImage(ccImage*);
	void fillWithCalibratedImage(ccCalibratedImage*);
	void fillWithLabel(cc2DLabel*);
	void fillWithViewportObject(cc2DViewportObject*);
	void fillWithGBLSensor(ccGBLSensor*);
	void fillWithCameraSensor(ccCameraSensor*);
	void fillWithMaterialSet(ccMaterialSet*);
	void fillWithShareable(CCShareable*);
	void fillWithMetaData(ccObject*);
	template<int N, class ElementType> void fillWithChunkedArray(ccChunkedArray<N,ElementType>*);

	//! Updates the current model (assuming object is the same)
	void updateModel();

	ccHObject* m_currentObject;
	QStandardItemModel* m_model;
	QAbstractItemView* m_view;
};

#endif
